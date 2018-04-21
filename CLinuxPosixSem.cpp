/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*文件描述：使用Linux系统调用实现的POSIX信号量类源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CLinuxPosixSem.h"

#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <stdexcept>

CLinuxPosixSem::CLinuxPosixSem(int initNum): CPosixSem(initNum)
{
    //初始化信号量，设初值
    if (-1 == sem_init(&m_sem, 0, (unsigned int)initNum))
    {
        throw std::logic_error("sem_init error!");
    }
}

CLinuxPosixSem::~CLinuxPosixSem()
{
    //释放信号量
    sem_destroy(&m_sem);
}

BOOL CLinuxPosixSem::Post()
{
    int ret = sem_post(&m_sem);
    return (0 == ret) ? TRUE : FALSE;
}

OS_RET_ENUM CLinuxPosixSem::Wait(int timeout_ms)
{
    int ret = -1;
    //-1为永远等待
    if(-1 == timeout_ms)
    {
        while(-1 == (ret = sem_wait(&m_sem)) && EINTR == errno);
        if (0 == ret)
        {
            return OS_RET_NORMAL;
        }
        else
        {
            return OS_RET_ERROR;
        }
    }
    timespec ts = {0, 0};  //设置最长等待时间
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout_ms / 1000;  //等待秒数
    ts.tv_nsec += timeout_ms % 1000 * 1000000;   //纳秒数
    if (ts.tv_nsec > 1000000000)
    {
        ts.tv_sec += 1;
        ts.tv_nsec -= 1000000000;
    }
    while(-1 == (ret = sem_timedwait(&m_sem, &ts)) && EINTR == errno);
    if (0 == ret)
    {
        return OS_RET_NORMAL;
    }
    else if(ETIMEDOUT == errno)
    {
        return OS_RET_TIMEOUT;
    }
    else
    {
        return OS_RET_ERROR;
    }
}

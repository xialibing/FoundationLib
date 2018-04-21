/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的互斥体类源文件
*修改记录：
*1.作者：xialibing 时间：2018.4.18，修改内容：创建
*/
#include "CLinuxMutex.h"
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <stdexcept>

CLinuxMutex::CLinuxMutex()
{
    //初始化信号量，设初值为1
    if(0 != sem_init(&m_sem, 0, 1))
    {
        throw std::logic_error("sem_init error!");
    }
}

CLinuxMutex::~CLinuxMutex()
{
    //解锁
    CLinuxMutex::UnLock();
    //释放信号量
    sem_destroy(&m_sem);
}

OS_RET_ENUM CLinuxMutex::Lock(int timeout_ms)
{
    int ret = -1;
    //-1为永远等待
    if(-1 == timeout_ms)
    {
        // 处理被信号打断的情况
        while(-1 ==(ret = sem_wait(&m_sem)) && EINTR == errno);
        if(0 == ret)
        {
            return OS_RET_NORMAL;
        }
        else
        {
            return OS_RET_ERROR;
        }
    }
    timespec ts = {0, 0};//设置最长等待时间
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout_ms / 1000;  //等待秒数
    ts.tv_nsec += timeout_ms % 1000 * 1000000;   //纳秒数
    if (ts.tv_nsec > 1000000000)
    {
        ts.tv_sec += 1;
        ts.tv_nsec -= 1000000000;
    }
    //处理被信号打断的情况
    while (-1 == (ret = sem_timedwait(&m_sem, &ts)) && EINTR == errno);
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

OS_RET_ENUM CLinuxMutex::TryLock()
{
    int ret = -1;
    while (-1 == (ret = sem_trywait(&m_sem)) && EINTR == errno);
    if (0 == ret)
    {
        return OS_RET_NORMAL;
    }
    else if(EAGAIN == errno)
    {
        return OS_RET_TIMEOUT;
    }
    else
    {
        return OS_RET_ERROR;
    }
}

void CLinuxMutex::UnLock()
{
    //如果锁已经是解开状态
    if(OS_LOCK_OFF == GetLockState())
    {
        return;
    }
    else
    {
        sem_post(&m_sem);
    }
}

OS_LOCK_ENUM CLinuxMutex::GetLockState()
{
    //获取信号量值
    int semval = 0;
    sem_getvalue(&m_sem, &semval);
    if (0 == semval)
    {
        return OS_LOCK_ON;
    }
    else
    {
        return OS_LOCK_OFF;
    }
}


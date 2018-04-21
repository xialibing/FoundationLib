/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的计时器类源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CLinuxTimer.h"
#include <sys/time.h>
#include <time.h>
#include <stdexcept>

CLinuxTimer::CLinuxTimer()
:m_msCount(0)
{
    //初始化线程锁
    if (0 != pthread_mutex_init(&m_Lock, NULL))
    {
        throw std::logic_error("pthread_mutex_init error!");
    }
}

CLinuxTimer::~CLinuxTimer()
{
    pthread_mutex_lock(&m_Lock);
    pthread_mutex_unlock(&m_Lock);
    //释放线程锁
    pthread_mutex_destroy(&m_Lock);
}

void CLinuxTimer::Start()
{
    timespec ts = {0, 0};
    //记录当前时刻
    clock_gettime(CLOCK_MONOTONIC, &ts);
    pthread_mutex_lock(&m_Lock);
    m_msCount = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    pthread_mutex_unlock(&m_Lock);
}

void CLinuxTimer::Stop(int &elapsedTime)
{
    timespec ts = {0, 0};
    //记录当前时刻
    clock_gettime(CLOCK_MONOTONIC, &ts);
    pthread_mutex_lock(&m_Lock);
    //得到与上次调用Start之间的毫秒数
    elapsedTime = ts.tv_sec * 1000 + ts.tv_nsec / 1000000 - m_msCount;
    pthread_mutex_unlock(&m_Lock);
}

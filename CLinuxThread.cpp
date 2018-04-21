/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*文件描述：使用Linux系统调用实现的线程类源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CLinuxThread.h"
#include <assert.h>
#include <sched.h>
#include <unistd.h>
#include <stdexcept>

CLinuxThread::CLinuxThread(void *(*startAddress)(void *), void *arg, int priority, OS_POLICY_ENUM policy)
: CThread(startAddress, arg, priority, policy), m_tid(0), m_bStart(false), m_bJoin(false)
{
    //线程参数
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //调度参数
    sched_param sp;
    sp.sched_priority = priority;

    //设置调度策略
    if (0 != pthread_attr_setschedpolicy(&attr, static_cast<int>(policy)))
    {
        throw std::logic_error("pthread_attr_setschedpolicy error!");
    }

    //设置优先级
    if (0 != pthread_attr_setschedparam(&attr, &sp))
    {
        throw std::logic_error("pthread_attr_setschedparam error!");
    }

//	if (0 != pthread_attr_setstacksize(&attr, 1024 * 1024))
//	{
//		throw std::logic_error("pthread_attr_setstacksize error!");
//	}

    StArg *thrArg = new StArg();
    thrArg->actualArg = arg;
    thrArg->thisPtr = this;
    thrArg->actualFunc = startAddress;

    //启动线程函数
    if (0 != pthread_create(&m_tid, &attr, TheadFunc, thrArg))
    {
        throw std::logic_error("pthread_create error!");
    }

    // 确认线程已经启动
    while (!m_bStart)
    {
        usleep(1000);
    }

    pthread_setschedparam(m_tid, static_cast<int>(policy), &sp);

    //销毁线程参数
    pthread_attr_destroy(&attr);
}

CLinuxThread::~CLinuxThread()
{
    // 确认线程已经启动
    while (!m_bStart)
    {
        usleep(1000);
    }
    //分离线程
    if (!m_bJoin)
    {
        pthread_detach(m_tid);
    }
}

int CLinuxThread::WaitForQuit(void **pRval)
{
    // 确认线程已经启动
    while (!m_bStart)
    {
        usleep(1000);
    }

    int ret = pthread_join(m_tid, pRval);

    m_bJoin = true;

    return ret;
}

void *CLinuxThread::TheadFunc(void *arg)
{
    StArg *thrArg = (StArg *)arg;
    // 设置线程为已启动
    thrArg->thisPtr->m_bStart = true;
    // 启动实际线程函数
    void *ret = thrArg->actualFunc(thrArg->actualArg);

    delete thrArg;

    return ret;
}

/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的线程类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CLINUXTHREAD_H
#define CLINUXTHREAD_H

#include "CThread.h"
#include <pthread.h>

class CLinuxThread : public CThread
{
public:
    CLinuxThread(void *(*startAddress)(void *), void *arg, int priority, OS_POLICY_ENUM policy);
    virtual ~CLinuxThread();

    virtual int WaitForQuit(void **pRval);
private:
    pthread_t m_tid;   /*!< 线程描述符*/
    bool m_bStart;     /*!< 线程启动标志*/
    bool m_bJoin;
    struct StArg
    {
        void *actualArg; /*!< 实际参数*/
        CLinuxThread *thisPtr; /*!< 当前线程对象地址*/
        void *(*actualFunc)(void *); /*!< 实际线程启动地址*/
    };

    static void *TheadFunc(void *);
};

#endif // CLINUXTHREAD_H

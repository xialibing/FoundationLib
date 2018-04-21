/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的计时器类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CLINUXTIMER_H
#define CLINUXTIMER_H

#include <CTimer.h>
#include "pthread.h"

class CLinuxTimer : public CTimer
{
public:
    CLinuxTimer();
    virtual ~CLinuxTimer();

    virtual void Start();

    virtual void Stop(int &elapsedTime);
private:
    int m_msCount;             /*!< 保存毫秒数*/
    pthread_mutex_t m_Lock;    /*!< 线程安全锁*/
};

#endif // CLINUXTIMER_H

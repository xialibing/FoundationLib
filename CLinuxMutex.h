/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的互斥体类
*修改记录：
*1.作者：xialibing时间：2018.4.18，修改内容：创建
*/

#ifndef CLINUXMUTEX_H
#define CLINUXMUTEX_H

#include <CMutex.h>
#include <semaphore.h>

class CLinuxMutex : public CMutex
{
public:
    CLinuxMutex();
    virtual ~ CLinuxMutex();
    /**
    *@brief 加锁
    *@param[in] timeout_ms -- 最长等待时间, 单位ms, -1为永远等待
    *@return OS_RET_NORMAL -- 正常加锁返回, OS_RET_TIMEOUT -- 超时返回
    */
    virtual OS_RET_ENUM Lock(int timeout_ms = -1);
    /**
      *@brief 同Lock(0)
     */
    virtual OS_RET_ENUM TryLock();
    /**
    *@brief 解锁
    */
    virtual void UnLock();
    /**
    *@brief 获取锁的状态
    *@return LOCK_ON -- 被锁住， LOCK_OFF -- 未锁住
    */
    virtual OS_LOCK_ENUM GetLockState();
private:
    CLinuxMutex(const CLinuxMutex &);   /*!< 禁止复制*/
    sem_t m_sem;     /*!< 信号量结构*/
};

#endif // CLINUXMUTEX_H

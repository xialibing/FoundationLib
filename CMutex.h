/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：互斥体资源实现接口，提供对操作系统调用的封装
*修改记录：
*1.作者：xialibing，时间：2018.4.16，修改内容：创建
*/

#ifndef CMUTEX_H
#define CMUTEX_H

#include <osenum.h>
#include <typedef.h>

class CMutex
{
public:
    CMutex();
    virtual ~CMutex() = 0;
    /**
    *@brief 加锁
    *@param[in] timeout_ms -- 最长等待时间, 单位ms, -1为永远等待
    *@return OS_RET_NORMAL -- 正常加锁返回, OS_RET_TIMEOUT -- 超时返回
    */
    virtual OS_RET_ENUM Lock(int timeout_ms = -1) = 0;
    /**
      *@brief 同Lock(0)
     */
    virtual OS_RET_ENUM TryLock() = 0;
    /**
    *@brief 解锁
    */
    virtual void UnLock() = 0;
    /**
    *@brief 获取锁的状态
    *@return LOCK_ON -- 被锁住， LOCK_OFF -- 未锁住
    */
    virtual OS_LOCK_ENUM GetLockState() = 0;

};

#endif // CMUTEX_H

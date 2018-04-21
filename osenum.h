/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：OS需要使用的枚举定义
*修改记录：
*1.作者：xialibing，时间：2018.4.16，修改内容：创建
*/

#ifndef OSENUM_H
#define OSENUM_H

/**
*函数返回值
*/
enum OS_RET_ENUM
{
    OS_RET_NORMAL = 0,  /*!< 正常返回*/
    OS_RET_TIMEOUT,     /*!< 超时返回,包括当前锁被锁住，尝试获取失败*/ //TryLock可能返回OS_RET_TIMEOUT？--OS_RET_TIMEOUT加注释
    OS_RET_ERROR        /*!< 错误返回*/
};
/**
*锁状态
*/
enum OS_LOCK_ENUM
{
    OS_LOCK_ON = 0, /*!< 被锁住*/
    OS_LOCK_OFF     /*!< 未锁住*/
};
/**
*线程调度策略
*/
enum OS_POLICY_ENUM
{
    OS_POLICY_OTHER = 0,    /*!<普通进程*/
    OS_POLICY_FIFO,         /*!<先入先出实时进程*/
    OS_POLICY_RR,           /*!<时间片轮转实时进程*/
};

#endif // OSENUM_H


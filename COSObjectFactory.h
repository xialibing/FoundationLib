/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：COSObjectFactory提供静态工厂方法，用于创建操作系统对象
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef COSOBJECTFACTORY_H
#define COSOBJECTFACTORY_H

#include "CMutex.h"
#include "CPipe.h"
#include "CSem.h"
#include "CShareMem.h"
#include "CThread.h"
#include "CTimer.h"
#include "CPosixSem.h"
#include "osenum.h"

class COSObjectFactory
{
public:
    /**
    *@brief 创建Mutex
    *@return Mutex指针
    *@note 创建出来的指针必须delete
    */
    static CMutex *CreateMutex();
    /**
    *@brief 创建Pipe
    *@return Pipe指针
    *@note 创建出来的指针必须delete
    */
    static CPipe *CreatePipe();
    /**
    *@brief 创建Sem
    *@param[in] initNum -- 信号量初始值
    *@return Sem指针
    *@note 创建出来的指针必须delete
    */
    static CSem *CreateSem(int initNum);
    /**
    *@brief 创建PosixSem
    *@param[in] initNum -- 信号量初始值
    *@return PosixSem指针
    *@note 创建出来的指针必须delete
    */
    static CPosixSem *CreatePosixSem(int initNum);

    //posixsem项目中没有使用, 隐藏接口

    /**
    *@brief 创建ShareMem
    *@param[in] startAddress -- 共享存储起始地址
    *@param[in] size -- 共享存储最大字节数
    *@param[in] fd -- 映射的文件描述符
    *@param[in] off -- 共享内存起始在文件中的偏移量
    *@return ShareMem指针
    *@note 创建出来的指针必须delete
    */
    static CShareMem *CreateShareMem(unsigned int startAddress, unsigned int size, int fd, unsigned int off);
    /**
    *@brief 创建Thread
    *@param[in] startAddress -- 线程起始地址
    *@param[in] arg -- 线程参数地址
    *@param[in] priority -- 线程优先级
    *@param[in] policy -- 调度策略
    *@return Thread指针
    *@note 创建出来的指针必须delete
    */
    static CThread *CreateThread(void *(*startAddress)(void *), void *arg, int priority, OS_POLICY_ENUM policy);
    /**
    *@brief 创建Timer
    *@return Timer指针
    *@note 创建出来的指针必须delete
    */
    static CTimer *CreateTimer();

    static void GetVersion(char version[], int len);
};

#endif // COSOBJECTFACTORY_H
// 这个工厂最好能做成抽象工厂，不要用这些静态方法--vfuture

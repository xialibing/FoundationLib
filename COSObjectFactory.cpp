/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：COSObjectFactory提供静态工厂方法，用于创建操作系统对象
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "COSObjectFactory.h"
#include "Version.h"
#include "CLinuxMutex.h"
#include "CLinuxPipe.h"
#include "CLinuxSem.h"
#include "CSleepSem.h"
#include "CLinuxShareMem.h"
#include "CLinuxThread.h"
#include "CLinuxTimer.h"
#include "CLinuxPosixSem.h"

#include <string.h>

CMutex *COSObjectFactory::CreateMutex()
{
    CMutex *pMutex = NULL;
    try
    {
        pMutex = new CLinuxMutex;
    }
    catch(...)
    {
        pMutex = NULL;
    }

    return pMutex;
}

CPipe *COSObjectFactory::CreatePipe()
{
    CPipe *pPipe = NULL;
    try
    {
        pPipe = new CLinuxPipe;
    }
    catch(...)
    {
        pPipe = NULL;
    }

    return pPipe;
}

CSem *COSObjectFactory::CreateSem(int initNum)
{
    CSem *pSem = NULL;
    try
    {
        pSem = new CSleepSem(initNum);
    }
    catch(...)
    {
        pSem = NULL;
    }
    return pSem;
}

CPosixSem *COSObjectFactory::CreatePosixSem(int initNum)
{
    CPosixSem *pSem = NULL;
    try
    {
        pSem = new CLinuxPosixSem(initNum);
    }
    catch(...)
    {
        pSem = NULL;
    }
    return pSem;
}

CShareMem *COSObjectFactory::CreateShareMem(unsigned int startAddress, unsigned int size, int fd, unsigned int off)
{
    CShareMem *pShareMem = NULL;
    try
    {
        pShareMem = new CLinuxShareMem(startAddress, size, fd, off);
    }
    catch(...)
    {
        pShareMem = NULL;
    }
    return pShareMem;
}

CThread *COSObjectFactory::CreateThread(void *(*startAddress)(void *), void *arg, int priority, OS_POLICY_ENUM policy)
{
    CThread *pThread = NULL;
    try
    {
        pThread = new CLinuxThread(startAddress, arg, priority, policy);
    }
    catch(...)
    {
        pThread = NULL;
    }
    return pThread;
}

CTimer *COSObjectFactory::CreateTimer()
{
    CTimer *pTimer = NULL;
    try
    {
        pTimer = new CLinuxTimer;
    }
    catch(...)
    {
        pTimer = NULL;
    }
    return pTimer;
}

void COSObjectFactory::GetVersion(char version[], int len)
{
    strcpy(version, LIB_FOUNDATION_VERSION);
}

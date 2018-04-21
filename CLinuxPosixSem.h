/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的POSIX信号量类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CLINUXPOSIXSEM_H
#define CLINUXPOSIXSEM_H

#include "CPosixSem.h"
#include <semaphore.h>

class CLinuxPosixSem: public CPosixSem
{
public:
    CLinuxPosixSem(int initNum);
    virtual ~CLinuxPosixSem();

    virtual BOOL Post();
    virtual OS_RET_ENUM Wait(int timeout_ms); //建议将timeout参数名改为timeout_ms，一眼就能知道是毫秒为单位
private:
    sem_t m_sem;     /*!< 信号量结构*/
};

#endif // CLINUXPOSIXSEM_H

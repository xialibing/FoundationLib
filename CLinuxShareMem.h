/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的共享内存类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CLINUXSHAREMEM_H
#define CLINUXSHAREMEM_H

#include "CShareMem.h"

class CLinuxShareMem : public CShareMem
{
public:
    CLinuxShareMem(unsigned int startAddress, unsigned int size, int fd, unsigned int off);
    virtual ~CLinuxShareMem();

    virtual unsigned int GetLength() { return m_length; }

    virtual void *GetRawBuffer() const { return m_memBuf; }

    virtual BOOL Sync();
private:
    unsigned int m_length;      /*!< 共享内存段长度*/

    void *m_memBuf;     /*!< 共享内存地址*/
};

#endif // CLINUXSHAREMEM_H

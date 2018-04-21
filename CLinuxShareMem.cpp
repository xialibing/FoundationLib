/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*文件描述：使用Linux系统调用实现的共享内存类源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CLinuxShareMem.h"
#include <sys/mman.h>
#include <stdio.h>

CLinuxShareMem::CLinuxShareMem(unsigned int startAddress, unsigned int size, int fd, unsigned int off):
CShareMem(startAddress, size, fd, off), m_length(size)
{
    //创建共享内存段
    m_memBuf = mmap((void *)startAddress, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)off);
}

CLinuxShareMem::~CLinuxShareMem()
{
    //解除共享映射区
    munmap(m_memBuf, m_length);
}

BOOL CLinuxShareMem::Sync()
{
    if (0 != msync(m_memBuf, m_length, MS_SYNC))
    {
        return false;
    }
    return true;
}


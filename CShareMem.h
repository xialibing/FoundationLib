/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：共享内存资源实现接口，提供对操作系统调用的封装
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CSHAREMEM_H
#define CSHAREMEM_H

#include "osenum.h"
#include "typedef.h"

class CShareMem
{
public:
    /**
    *@brief 构造函数
    *@param[in] startAddress -- 共享存储起始地址
    *@param[in] size -- 共享存储最大字节数
    *@param[in] fd -- 映射的文件描述符
    *@param[in] off -- 共享内存起始在文件中的偏移量
    */
    CShareMem(unsigned int startAddress, unsigned int size, int fd, unsigned int off);
    virtual ~CShareMem() = 0;
    /**
    *@brief 获取共享内存长度
    *@return 共享内存长度
    */
    virtual unsigned int GetLength() = 0;
    /**
    *@brief 获取原始地址
    *@return 原始地址
    */
    virtual void *GetRawBuffer() const = 0;

    virtual BOOL Sync() = 0;
};

#endif // CSHAREMEM_H

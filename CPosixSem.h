/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：POSIX信号量实现类接口，封装操作系统调用, 提供精确的信号量超时等待机制
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CPOSIXSEM_H
#define CPOSIXSEM_H

#include "osenum.h"
#include "typedef.h"

class CPosixSem
{
public:
    /**
    *@brief
    *@param[in] initNum -- 信号量初始值
    */
    CPosixSem(int initNum);
    virtual ~CPosixSem() = 0;
    /**
    *@brief 释放信号量
    *@return TRUE - 释放成功
    *@note 如果num<0，则会转换成-num
    */
    virtual BOOL Post() = 0;
    /**
    *@brief 请求信号量
    *@param[in] timeout_ms -- 最长等待时间, 单位ms, -1为永远等待
    *@return RETNORMAL-正常返回  RET_TIMEOUT- 超时返回， RET_ERROR - 错误返回
    *@note 如果num<0，则会转换成-num
    */
    virtual OS_RET_ENUM Wait(int timeout_ms) = 0;
};

#endif // CPOSIXSEM_H

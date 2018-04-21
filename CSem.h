/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：信号量实现类接口，封装操作系统调用
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CSEM_H
#define CSEM_H

#include "osenum.h"
#include "typedef.h"

class CSem
{
public:
    /**
    *@param[in] initNum -- 信号量初始值
    */
    CSem(int initNum);
    virtual ~CSem() = 0;
    /**
    *@brief 释放信号量
    *@param[in] num -- 释放信号量个数
    *@return TRUE - 释放成功
    *@note 如果num<0，则会转换成-num
    */
    virtual BOOL Up(unsigned short num) = 0;
    /**
    *@brief 设置信号量值
    *@param[in] num -- 设置信号量值
    *@return TRUE - 设置成功
    */
    virtual BOOL SetValue(unsigned short num) = 0;
    /**
    *@brief 请求信号量
    *@param[in] num -- 请求信号量个数
    *@param[in] timeout_ms -- 最长等待时间, 单位ms, -1为永远等待
    *@return RETNORMAL-正常返回  RET_TIMEOUT- 超时返回， RET_ERROR - 错误返回
    *@note 如果num<0，则会转换成-num
    */
    virtual OS_RET_ENUM Down(unsigned short num, int timeout_ms) = 0;
    /**
    *@brief 等待信号量值变成0
    *@param[in] timeout_ms -- 最长等待时间, 单位ms, -1为永远等待
    *@return  RETNORMAL-正常返回  RET_TIMEOUT- 超时返回， RET_ERROR - 错误返回
    */
    virtual OS_RET_ENUM WaitForZero(int timeout_ms) = 0;
};

#endif // CSEM_H

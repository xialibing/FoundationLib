/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：线程资源实现接口，提供对操作系统调用的封装
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CTHREAD_H
#define CTHREAD_H

#include "osenum.h"
#include "typedef.h"
#include <stddef.h>

class CThread
{
public:
    /**
    *@brief 构造函数
    *@param[in] startAddress -- 线程起始地址
    *@param[in] arg -- 线程参数地址
    *@param[in] priority -- 线程优先级
    *@param[in] policy -- 调度策略
    */
    CThread(void *(*startAddress)(void *), void *arg, int priority, OS_POLICY_ENUM policy);
    virtual ~CThread() = 0;

    /**
    *@brief 等待线程结束
    *@param[out] pRval -- 线程返回值
    *@return 成功返回0，否则返回错误编号
    */
    virtual int WaitForQuit(void **pRval) = 0;  //两个WaitForQuit合并为一个
};

#endif // CTHREAD_H

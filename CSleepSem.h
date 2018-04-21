/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用usleep调用实现超时机制的信号量类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CSLEEPSEM_H
#define CSLEEPSEM_H

#include "CSem.h"

//建议详细说明一下为什么使用sleep来实现超时时间控制
//semtimedop的超时计时不够准确
class CSleepSem : public CSem
{
public:
    CSleepSem(int initNum);
    virtual ~CSleepSem();
    virtual BOOL Up(unsigned short num);
    virtual BOOL SetValue(unsigned short num);
    virtual OS_RET_ENUM Down(unsigned short num, int timeout_ms);
    virtual OS_RET_ENUM WaitForZero(int timeout_ms);
private:
    int m_semId;         /*!< 信号量Id*/
};

#endif // CSLEEPSEM_H

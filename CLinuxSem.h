/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的信号量类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CLINUXSEM_H
#define CLINUXSEM_H

#include "CSem.h"

class CLinuxSem : public CSem
{
public:
    CLinuxSem(int initNum);
    virtual ~CLinuxSem();

    virtual BOOL Up(unsigned short num);
    virtual BOOL SetValue(unsigned short num);
    virtual OS_RET_ENUM Down(unsigned short num, int timeout_ms);
    virtual OS_RET_ENUM WaitForZero(int timeout_ms);
private:
    int m_semId;         /*!< 信号量Id*/
};

#endif // CLINUXSEM_H

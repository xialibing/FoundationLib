/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*类描述：使用Linux系统调用实现的管道类
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CLINUXPIPE_H
#define CLINUXPIPE_H

#include "CPipe.h"
#include "typedef.h"

#include <pthread.h>

class CLinuxPipe : public CPipe
{
public:
    CLinuxPipe();
    virtual ~CLinuxPipe();

    virtual int Read(void *buffer, unsigned int len, int timeout_ms);
    virtual int Write(const void *buffer, unsigned int len);
private:
    int m_fd[2];          /*!< 管道描述符 */
    BOOL m_isValid;       /*!< 管道是否有效*/
};

#endif // CLINUXPIPE_H

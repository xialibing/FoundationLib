/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*文件描述：使用Linux系统调用实现的管道类源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CLinuxPipe.h"
#include <unistd.h>
#include <sys/select.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdexcept>

CLinuxPipe::CLinuxPipe():m_isValid(FALSE)
{
    //创建管道
    m_isValid = (BOOL)pipe(m_fd);
}

CLinuxPipe::~CLinuxPipe()
{
    //关闭管道
    if(FALSE != m_isValid)
    {
        close(m_fd[0]);
        close(m_fd[1]);
    }
}

int CLinuxPipe::Read(void *buffer, unsigned int len, int timeout_ms)
{
    if(FALSE == m_isValid)
    {
        return -1;
    }
    //读管道，read操作由系统保证线程安全
    int ret = 0;
    //如果不设置超时时间，则直接调用read
    if(timeout_ms < 0)
    {
        ret = read(m_fd[0], buffer, len);
    }
    //否则调用select等待
    else
    {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(m_fd[0], &readset);
        //设置超时时间
        timeval tv = {0};
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = timeout_ms % 1000 * 1000;

        int selectRet = select(m_fd[0] + 1, &readset, NULL, NULL, &tv);
        if(0 == selectRet)
        {
            ret = 0;
        }
        else
        {
            ret = read(m_fd[0], buffer, len);
        }
    }

    return ret;
}

int CLinuxPipe::Write(const void *buffer, unsigned int len)
{
    if(FALSE == m_isValid)
    {
        return -1;
    }

    //写管道，操作系统的write调用保证了当一次写入字节数小于PIPE_BUF时，写操作线程安全
    int ret = 0;
    ret = write(m_fd[1], buffer, len);

    return ret;
}

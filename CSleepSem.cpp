/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*文件描述：使用usleep调用实现超时机制的信号量源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CSleepSem.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

union semun {
    int              val;    /*!< 信号量SETVAL操作数值 */
    struct semid_ds *buf;    /*!< 信号量集的semid_ds参数地址，供IPC_STAT, IPC_SET操作用 */
    unsigned short  *array;  /*!< 存储所有信号量值的数组，供GETALL, SETALL使用 */
    struct seminfo  *__buf;  /*!< Buffer for IPC_INFO	 (Linux-specific) */
};

CSleepSem::CSleepSem(int initNum)
:CSem(initNum), m_semId(0)
{
    //创建信号量
    m_semId = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (-1 != m_semId)
    {
        semun semunion;
        semunion.val = initNum;
        //设置初始值
        if (0 != semctl(m_semId, 0, SETVAL, semunion))
        {
            m_semId = -1;
        }
    }
    else
    {
        perror("semget fail");
    }
}

CSleepSem::~CSleepSem()
{
    //释放信号量
    if (-1 != m_semId)
    {
        semctl(m_semId, 0, IPC_RMID);
    }
}

BOOL CSleepSem::Up(unsigned short num)
{
    if (-1 == m_semId)
    {
        return FALSE;
    }
    if (num < 0)
    {
        num = -num;
    }
    sembuf semops;
    semops.sem_num = 0;
    semops.sem_op = num;
    semops.sem_flg = SEM_UNDO;

    int ret = -1;
    while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
    if (0 == ret)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CSleepSem::SetValue(unsigned short num)
{
    if (-1 == m_semId)
    {
        return FALSE;
    }
    semun semvalue;
    semvalue.val = num;
    if (0 == semctl(m_semId, 0, SETVAL, semvalue))
    {
        return TRUE;
    }
    else
    {
        perror("sem up fail");
        return FALSE;
    }
}

OS_RET_ENUM CSleepSem::Down(unsigned short num, int timeout_ms)
{
    if (-1 == m_semId)
    {
        return OS_RET_ERROR;
    }
    if (num < 0)
    {
        num = -num;
    }
    sembuf semops;
    semops.sem_num = 0;
    semops.sem_op = -num;
    semops.sem_flg = SEM_UNDO;
    if (0 <= timeout_ms)
    {
        semops.sem_flg |= IPC_NOWAIT;
    }

    int ret = 0;
    //timeout < 0 代表一直等待, 调用semop
    if(timeout_ms < 0)
    {
        while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
        if(0 == ret)
        {
            return OS_RET_NORMAL;
        }
        else if(EAGAIN == errno)
        {
            return OS_RET_TIMEOUT;
        }
        else
        {
            return OS_RET_ERROR;
        }
    }
    else
    {
        int loop = 0;
        for (loop = 0; loop <= timeout_ms; loop++)
        {
            while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
            if (0 == ret)
            {
                return OS_RET_NORMAL;
            }
            else if (EAGAIN == errno)
            {
                if (loop == timeout_ms)
                {
                    return OS_RET_TIMEOUT;
                }
                usleep(1000);
            }
            else
            {
                return OS_RET_ERROR;
            }
        }
        return OS_RET_TIMEOUT;
    }
}

OS_RET_ENUM CSleepSem::WaitForZero(int timeout_ms)
{
    if (-1 == m_semId)
    {
        return OS_RET_ERROR;
    }

    sembuf semops;
    semops.sem_num = 0;
    semops.sem_op = 0;
    semops.sem_flg = SEM_UNDO;
    if (0 <= timeout_ms)
    {
        semops.sem_flg |= IPC_NOWAIT;
    }

    int ret = 0;
    //timeout < 0 代表一直等待, 调用semop
    if(timeout_ms < 0)
    {
        while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
        if(0 == ret)
        {
            return OS_RET_NORMAL;
        }
        else if(EAGAIN == errno)
        {
            return OS_RET_TIMEOUT;
        }
        else
        {
            perror("sem down fail");
            return OS_RET_ERROR;
        }
    }
    else
    {
        int loop = 0;
        for (loop = 0; loop <= timeout_ms; loop++)
        {
            while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
            if (0 == ret)
            {
                return OS_RET_NORMAL;
            }
            else if (EAGAIN == errno)
            {
                if (loop == timeout_ms)
                {
                    return OS_RET_TIMEOUT;
                }
                usleep(1000);
            }
            else
            {
                return OS_RET_ERROR;
            }
        }
        return OS_RET_TIMEOUT;
    }
}

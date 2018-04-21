/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*文件描述：使用Linux系统调用实现的信号量类源文件
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#include "CLinuxSem.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

union semun {
    int              val;    /*!< 信号量SETVAL操作数值 */
    struct semid_ds *buf;    /*!< 信号量集的semid_ds参数地址，供IPC_STAT, IPC_SET操作用 */
    unsigned short  *array;  /*!< 存储所有信号量值的数组，供GETALL, SETALL使用 */
    struct seminfo  *__buf;  /*!< Buffer for IPC_INFO	 (Linux-specific) */
};

CLinuxSem::CLinuxSem(int initNum)
:CSem(initNum), m_semId(0)
{
    //创建信号量
    m_semId = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (-1 != m_semId)
    {
        semun semunion;
        semunion.val = initNum;
        //设置初始值
        semctl(m_semId, 0, SETVAL, semunion);
    }
    //构造函数中的异常应该如何处理？else中为空，不合适，assert+抛异常（包含errno）
    //方法内会判断m_semId是否为-1
}
//CLinuxSem::~CLinuxSem中没有判断semctl的返回值，析构函数中不宜使用抛异常，是否可以考虑有个记错误日志的地方。只记导致错误的日志，暂时可以用个宏LogError来实现，不要使用printf，其他类也有类似问题--vecr1.0
CLinuxSem::~CLinuxSem()
{
    //释放信号量
    if (-1 != m_semId)
    {
        semctl(m_semId, 0, IPC_RMID);
    }
}

BOOL CLinuxSem::Up(unsigned short num)
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

BOOL CLinuxSem::SetValue(unsigned short num)
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
        return FALSE;
    }
}

OS_RET_ENUM CLinuxSem::Down(unsigned short num, int timeout_ms)
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
    if (0 == timeout_ms)
    {
        semops.sem_flg |= IPC_NOWAIT;
    }

    int ret = 0;
    //timeout == -1 代表一直等待, 调用semop, 否则调用semtimedop
    //这里的wait没有超时值用的是-1，sem里面只判断是否小于0，有些不一致。尽量接口一致
    if(timeout_ms == -1)
    {
        while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
    }
    else
    {
        timespec ts = {0, 0};  //设置最长等待时间
        ts.tv_sec = timeout_ms / 1000;  //等待秒数
        ts.tv_nsec = timeout_ms % 1000 * 1000000;   //纳秒数
        while (-1 == (ret = semtimedop(m_semId, &semops, 1, &ts)) && EINTR == errno);
    }
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

OS_RET_ENUM CLinuxSem::WaitForZero(int timeout_ms)
{
    if (-1 == m_semId)
    {
        return OS_RET_ERROR;
    }

    sembuf semops;
    semops.sem_num = 0;
    semops.sem_op = 0;
    semops.sem_flg = SEM_UNDO;
    if (0 == timeout_ms)
    {
        semops.sem_flg |= IPC_NOWAIT;
    }
    int ret = 0;
    //timeout == -1 代表一直等待, 调用semop, 否则调用semtimedop
    if(timeout_ms == -1)
    {
        while (-1 == (ret = semop(m_semId, &semops, 1)) && EINTR == errno);
    }
    else
    {
        timespec ts = {0, 0};  //设置最长等待时间
        ts.tv_sec = timeout_ms / 1000;  //等待秒数
        ts.tv_nsec = timeout_ms % 1000 * 1000000;   //纳秒数
        while (-1 == (ret = semtimedop(m_semId, &semops, 1, &ts)) && EINTR == errno);
    }

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

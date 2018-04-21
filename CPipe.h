/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：管道资源实现接口，提供对操作系统调用的封装
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CPIPE_H
#define CPIPE_H

class CPipe
{
public:
    CPipe();
    /*
    *@note 析构时保证线程安全
    */
    virtual ~CPipe() = 0;
    /**
    *@brief 从管道中读数据
    *@param[out] buffer -- 读取数据缓冲区地址
    *@param[in] len -- 希望读取的数据字节长度
    *@param[in] timeout_ms -- read timeout(ms), -1 -- wait forever
    *@return 实际读取的字节长度，-1为读取出错
    *@note buffer的生命期由调用端负责, 通过加锁保证线程安全性
    */
    virtual int Read(void *buffer, unsigned int len, int timeout_ms) = 0;
    /**
    *@brief 向管道中写数据
    *@param[in] buffer -- 写入数据缓冲区地址
    *@param[in] len -- 希望写入的数据字节长度
    *@return 实际写入的字节长度，-1为写入出错
    *@note 当len < 4096时, 可以保证线程安全性
    */
    virtual int Write(const void *buffer, unsigned int len) = 0;
};

#endif // CPIPE_H

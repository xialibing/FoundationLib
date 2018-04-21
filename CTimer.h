/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：计时器资源实现接口，提供对操作系统调用的封装
*修改记录：
*1.作者：xialibing，时间：2018.4.19，修改内容：创建
*/
#ifndef CTIMER_H
#define CTIMER_H

class CTimer
{
public:
    CTimer();
    virtual ~CTimer() = 0;
    /**
    *@brief  开始计时
    *@note 保证线程安全
    */
    virtual void Start() = 0;
    /**
    *@brief 停止计时
    *@param[out] elapsedTime -- 自上一次调用Start后经过的毫秒数
    *@note 计时功能限一天之内, 保证线程安全
    */
    virtual void Stop(int &elapsedTime) = 0;
};

#endif // CTIMER_H

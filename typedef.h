/**
*Copyright (c) 2018, xialibing
*All rights reserved。
*接口描述：数据类型定义
*修改记录：
*1.作者：xialibing，时间：2018.4.16，修改内容：创建
*/

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <assert.h>

#ifndef UINT
    typedef unsigned int		UINT;
#endif
#ifndef LONG
    typedef long       			LONG;
#endif
#ifndef WPARAM
    typedef unsigned long       WPARAM;
#endif
#ifndef LPARAM
    typedef LONG	            LPARAM;
#endif

#ifndef BOOL
    typedef unsigned int		BOOL;
#endif

#ifndef LRESULT
    typedef LONG	            LRESULT;
#endif

#ifndef TRUE
#define TRUE 0
#endif

#ifndef FALSE
#define FALSE ((unsigned int)-1)
#endif

void PrintStack(int signo);

# define Assert(expr)							\
  ((expr)								\
   ? __ASSERT_VOID_CAST (0)						\
   : (PrintStack(0), assert(expr)))

#ifdef DEBUG
#include <stdio.h>
#define PTRACE printf
#else
#define PTRACE
#endif

#endif // TYPEDEF_H


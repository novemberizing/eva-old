/**
 * @file        x/std.c
 * @brief       표준 라이브러리 구현 소스 파일입니다.
 * @details     
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "std.h"
#include "thread.h"

extern void xrandominit()
{
    srandom(time(xnil));
}

extern xint64 xrandomget(void)
{
    return random();
}

extern xuint64 xrandomunsigned64(xuint64 max)
{
    xuint64 n = (xuint64) random();
    return max == 0 ? n : (n % max);
}

extern xint64 xrandominteger64(xuint64 max)
{
    xuint64 n = (xuint64) random();
    return (xint64)(max == 0 ? n : (n % max)) * (random() % 2 ? -1 : 1);
}

extern xuint64 xunsigned64from_integer32(xint32 first, xint32 second)
{
    xuint64 ret = 0;

    xuint32 * n = (xuint32 *) xaddressof(ret);

    n[0] = first;
    n[1] = second;

    return ret;
}
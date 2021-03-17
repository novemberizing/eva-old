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
    return n % (max == 0 ? 1 : max);
}

extern xint64 xrandominteger64(xuint64 max)
{
    xuint64 n = (xuint64) random();
    return (xint64)(n % (max == 0 ? 1 : max)) * (random() % 2 ? -1 : 1);
}
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

#include "exception.h"

extern void xexceptionset(xexception * exception, void * func, xint32 number, xuint32 type, const char * message)
{
    xassertion(exception == xnil, "");

    if(exception->type == xexceptiontype_void)
    {
        exception->func = func;
        exception->number = number;
        exception->type = type;
        exception->message = message;
    }
}


/**
 * @fn          extern xint32 xexceptionno(xint32 number)
 * @brief       양수의 에러 번호를 음수로 치환합니다.
 * @details     주어진 파라미터가 음수이거나 0 이면 변환하지 않습니다.
 * 
 * @param       number | xint32 | in | 에러 번호 |
 * 
 * @return      | xint32 | 음수로 변환된 에러 번호 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
extern xint32 xexceptionno(xint32 number)
{
    return number > 0 ? -number : number;
}

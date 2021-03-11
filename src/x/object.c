/**
 * @file        x/object.c
 * @brief       객체 관련 메서드의 구현 파일입니다.
 * @details     객체는 스택이나 힙에 존재하는 선형적인 메모리 공간을 의미합니다.
 *              객체에 저장된 것은 선형적인 메모리 공간의 시작 주소입니다.
 *              
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "std.h"
#include "thread.h"

/**
 * @fn          extern xobject xobjectnew(const xobject data, xuint64 size)
 * @brief       새로운 객체를 생성합니다.
 *              특정 크기의 초기화된 메모리 공간을 생성합니다.
 * 
 * 
 * @param       size | xuint64 | in | 메모리 공간의 크기 |
 * 
 * @return      | xobject | 메모리 공간의 주소 |
 * 
 * @see         xobject
 *              calloc
 * 
 * @exception   | `size == 0` | 사이즈가 존재하지 않으면 예외를 발생시킵니다. |
 * 
 *                  SIZE 가 0 이면 널을 리턴하게 하는 것을 어떨까?
 * 
 *              | `o == xnil` | 메모리 할당에 실패하면 예외를 발생시킵나다. |
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
extern xobject xobjectnew(xuint64 size)
{
    xlogfunction_start("%s(%lu)", __func__, size);
    xassertion(size == 0, "");

    xobject o = calloc(size, 1);

    xassertion(o == xnil, "");

    xlogfunction_end("%s(...) => %p", __func__, o);

    return o;
}

/**
 * @fn          extern xobject xobjectdup(const xobject data, xuint64 size)
 * @brief       원본 객체와 동일한 객체를 메모리 공간에 생성하고 리턴합니다.
 * @details     메모리 공간에 원본 데이터의 크기만큼의 공간을 할당하고,
 *              원본 객체의 메모리를 카피하여 리턴합니다.
 * 
 * @param       data | const xobject | in | 원본 데이터 |
 * @param       size | xuint64       | in | 원본 데이터의 크기 |
 * 
 * @return      | xobject | 복제된 메모리 공간의 주소 |
 * 
 * @see         xobject
 *              malloc
 *              memcpy
 * 
 * @exception   | `data == xnil || size == 0` | 원본 객체가 존재하지 않거나 복제하려는 크기가 0 인 경우 예외를 발생시킵니다. |
 *              | `o == xnil`                 | 메모리 할당에 실패하면 예외를 발생시킵니다. |
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 *                  
 */
extern xobject xobjectdup(const void * data, xuint64 size)
{
    xlogfunction_start("%s(%p, %lu)", __func__, data, size);
    xassertion(data == xnil || size == 0, "");

    void * o = malloc(size);

    xassertion(o == xnil, "");

    void * ret = memcpy(o, data, size);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xobject xobjectrem(xobject o)
 * @brief       메모리 공간에 할당된 객체를 해제합니다.
 * @details     객체의 주소가 존재할 경우만 해제합니다.
 *              free 함수 역시 파라미터 값이 널일 경우 예외를 발생시키지 않지만,
 *              간헐적으로 널일 경우 예외를 발생시키는 케이스가 존재하기 때문에,
 *              널 체크를 하도록 하였습니다.
 * 
 * @param       o | xobject | in | 객체 |
 * 
 * @return      | xobject | 객체 |
 * 
 * @see         free
 *              xobject
 * 
 * @version     0.0.1
 * @date        2020. 02. 22.
 */
extern xobject xobjectrem(xobject o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    if(o)
    {
        free(o);
    }
    
    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}
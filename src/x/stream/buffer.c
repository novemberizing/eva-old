#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

#include "../thread.h"

const static xuint64 xstreambuffer_capacity_page = 4096;    /**!< 메모리 공간 기본 페이지 크기 */

/**
 * @fn          extern xstreambuffer * xstreambuffer_new(void)
 * @brief       바이트 스트림 객체를 생성합니다.
 * @details
 * 
 * @return      | xstreambuffer * | 바이트 스트림 객체 |
 * 
 * @see         xstreambuffer
 *              calloc
 *              xstreamtype_buffer
 *              xstreambuffer_capacity_page
 *              malloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xstreambuffer * xstreambuffer_new(void)
{
    xlogfunction_start("%s()", __func__);
    xstreambuffer * o = (xstreambuffer *) calloc(sizeof(xstreambuffer), 1);

    o->type     = xstreamtype_buffer;
    o->rem      = xstreambuffer_rem;
    o->capacity = xstreambuffer_capacity_page;
    o->buffer   = malloc(o->capacity);

    xlogfunction_end("%s(...) => %p", __func__, o);
    return o;
}

/**
 * @fn          extern xstreambuffer * xstreambuffer_rem(xstreambuffer * o)
 * @brief       바이트 스트림 객체의 소멸자
 * @details     
 * 
 * @param       o | xstreambuffer * | in | 바이트 스트림 객체 |
 * 
 * @return      | xstreambuffer * | 항상 널을 리턴합니다. |
 * @see         xstreambuffer
 *              free
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xstreambuffer * xstreambuffer_rem(xstreambuffer * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xassertion(o->rem != xstreambuffer_rem, "");

    if(o->buffer)
    {
        free(o->buffer);
    }
    free(o);

    xlogfunction_end("%s(...) => %p", __func__, xnil);
    return xnil;
}

/**
 * @fn          extern xbyte * xstreambuffer_back(xstreambuffer * o)
 * @brief       바이트 스트림 객체에서 사용할 수 있는 메모리 공간의 시작 주소 값을 리턴합니다.
 * @details
 * 
 * @param       o | xstreambuffer * | in | 바이트 스트림 버퍼 |
 * 
 * @return      | xbyte * | 사용할 수 있는 바이트 배열의 시작 주소 값 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xbyte * xstreambuffer_back(xstreambuffer * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xbyte * ret = (o->size == o->capacity ? xnil : xaddressof(o->buffer[o->size]));

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xbyte * xstreambuffer_front(xstreambuffer * o)
 * @brief       바이트 스트림 객체의 사용중인 데이터의 시작 주소 값을 리턴합니다.
 * @details
 * 
 * @param       o | xstreambuffer * | in | 바이트 스트림 객체 |
 * @return      | xbyte * | 사용중인 데이터의 시작 주소 값 |
 * 
 * @see         xstreambuffer
 *              xaddressof
 */
extern xbyte * xstreambuffer_front(xstreambuffer * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xbyte * ret = xaddressof(o->buffer[o->position]);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreambuffer_remain(xstreambuffer * o)
 * @brief       사용가능한 데이터 공간의 크기를 리턴합니다.
 * @details
 * 
 * 
 * @param       o | xstreambuffer * | in | 바이트 스트림 객체 |
 * @return      | xuint64 | 사용 가능한 데이터 공간의 크기 |
 * 
 * @see         xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreambuffer_remain(xstreambuffer * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xuint64 ret = (o->capacity - o->size);

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreambuffer_len(xstreambuffer * o)
 * @brief       남은 데이터의 크기
 * @param       o | xstreambuffer * | in | 스트림 객체 |
 * @return      | xuint64 | 남은 데이터의 크기 |
 * 
 * @see         xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreambuffer_len(xstreambuffer * o)
{
    xlogfunction_start("%s(%p)", __func__, o);
    xuint64 ret = (o->size - o->position);

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreambuffercapacity_set(xstreambuffer * o, xuint64 v)
 * @brief       전체 수용 가능 공간의 크기 설정
 * @details     전체 수용 가능 공간의 크기는 페이지 단위로 증가하게 됩니다.
 * 
 *              페이지 크기를 통한 수용 가능 공간을 구하는 공식은 아래와 같습니다.
 * 
 *              ```
 *              xuint64 capacity = (v / xstreambuffer_capacity_page + 1) * xstreambuffer_capacity_page;
 *              ```
 * 
 * @param       o | xstreambuffer * | in | 스트림 객체의 크기 |
 * @param       v | xuint64         | in | 설정하고자 하는 저장 공간의 크기 |
 * @return      | xuint64 | 설정된 데이터 공간의 크기 |
 * 
 * @see         xstreambuffer_capacity_page
 *              realloc
 *              malloc
 */
extern xuint64 xstreambuffercapacity_set(xstreambuffer * o, xuint64 v)
{
    xlogfunction_start("%s(%p, %lu)", __func__, o, v);
    xassertion(v < o->size, "");

    xuint64 capacity = (v / xstreambuffer_capacity_page + 1) * xstreambuffer_capacity_page;

    if(o->buffer)
    {
        if(o->capacity != capacity)
        {
            o->buffer = realloc(o->buffer, capacity);
        }
    }
    else
    {
        o->buffer = malloc(capacity);
    }

    o->capacity = capacity;

    xlogfunction_end("%s(...) => %lu", __func__, capacity);
    return capacity;
}

/**
 * @fn          extern xuint64 xstreambuffercapacity_get(xstreambuffer * o)
 * @brief       수용 가능 메모리 공간의 크기를 리턴합니다.
 * @details
 * 
 * @param       | o | xstreambuffer * | in | 스트림 버퍼 객체 |
 * @return      | xuint64 | 메모리 공간의 크기를 리턴합니다. |
 * 
 * @see         xstreambuffer
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreambuffercapacity_get(xstreambuffer * o)
{
    return o->capacity;
}

/**
 * @fn          extern xuint64 xstreambuffersize_set(xstreambuffer * o, xuint64 n)
 * @brief       사용한 메모리 공간의 크기를 설정합니다.
 * @details
 * 
 * @param       o | xstreambuffer * | in | 스트림 버퍼 객체 |
 * @param       n | xuint64         | in | 스트림 버퍼의 크기 |
 * 
 * @return      | xuint64 | 스트림 버퍼의 사용한 메모리 크기 |
 * 
 * @see         xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreambuffersize_set(xstreambuffer * o, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, o, n);

    xassertion(o->capacity < n, "");
    xuint64 ret = (o->size = n);

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreambuffersize_get(xstreambuffer * o)
 * @brief       바이트 스트림 객체의 사용한 메모리 공간의 크기
 * @details     
 * 
 * @param       o | xstreambuffer * | in | 스트림 객체 |
 * 
 * @return      | xuint64 | 스트림 버퍼의 크기 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreambuffersize_get(xstreambuffer * o)
{
    return o->size;
}

/**
 * @fn          extern xuint64 xstreambufferpos_set(xstreambuffer * o, xuint64 n)
 * @brief       스트림 버퍼의 사용한 데이터 인덱스
 * @details
 * 
 * @param       o | xstreambuffer * | in | 바이트 스트림 버퍼 |
 * @param       n | xuint64         | in | 사용한 데이터 인덱스 |
 * @return      | xuint64 | 설정된 데이터 인덱스 |
 */
extern xuint64 xstreambufferpos_set(xstreambuffer * o, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, o, n);

    xassertion(o->size < n, "");
    xuint64 ret = (o->position = n);

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreambufferpos_get(xstreambuffer * o)
 * @brief       스트림 버퍼의 사용한 인덱스를 리턴합니다.
 * @details
 * 
 * @param       o | xstreambuffer * | in | 스트림 버퍼 객체 |
 * @return      | xuint64 | 사용한 메모리 인덱스 |
 */
extern xuint64 xstreambufferpos_get(xstreambuffer * o)
{
    return o->position;
}

/**
 * @fn          extern xuint64 xstreambuffer_adjust(xstreambuffer * o, xint32 force)
 * @brief       스트림 버퍼를 보정합니다.
 * @details
 * 
 * @param       o | xstreambuffer * | in | 스트림 버퍼 객체 |
 * @param       force | xint32 | in | 강제적 보정 플래그 |
 * 
 * @return      | xuint64 | 수용가능한 데이터 공간의 크기 |
 * 
 * @see         xstreambuffer
 *              xaddressof
 *              memcpy
 *              memmove
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreambuffer_adjust(xstreambuffer * o, xint32 force)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, force);

    xuint64 len = o->size - o->position;
    if(o->position > 0)
    {
        if(len > 0)
        {
            if(len <= o->position)
            {
                memcpy(o->buffer, xaddressof(o->buffer[o->position]), len);
                o->position = 0;
                o->size = len;
            }
            else if(force)
            {
                memmove(o->buffer, xaddressof(o->buffer[o->position]), len);
                o->position = 0;
                o->size = len;
            }
        }
        else
        {
            o->position = 0;
            o->size = 0;
        }
    }

    xuint64 ret = o->capacity - o->size;

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

extern xuint64 xstreambuffer_push(xstreambuffer * o, const xbyte * data, xuint64 len)
{
    xlogfunction_start("%s(%p, %p, %lu)", __func__, o, data, len);
    // TODO: 최적화를 수행하가면서 데이터를 삽입하도록 한다.
    if(len < o->position + (o->capacity - o->size))
    {
        xstreambuffer_adjust(o, xtrue);
    }
    else
    {
        xstreambuffercapacity_set(o, xstreambuffercapacity_get(o) + len);
    }
    memcpy(xaddressof(o->buffer[o->size]), data, len);
    o->size = o->size + len;

    xuint64 ret = (o->size - o->position);

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

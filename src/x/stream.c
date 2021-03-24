/**
 * @file        x/stream.c
 * @brief       스트립 인터페이스의 구현 소스 파일입니다.
 * @details
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stream.h"

#include "thread.h"
#include "stream/buffer.h"

/**
 * @fn          extern xstream * xstreamnew(xuint32 type)
 * @brief       스트림 객체를 생성합니다.
 * 
 * @param       type | xuint32 | in | 스트림 객체의 타입 |
 * 
 * @return      | xstream | in | 스트림 객체 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambuffernew
 * 
 * @version     0.0.1
 */
extern xstream * xstreamnew(xuint32 type)
{
    xlogfunction_start("%s(%u)", __func__, type);

    xstream * ret = xnil;
    switch(type)
    {
        case xstreamtype_buffer:    ret = (xstream *) xstreambuffer_new();  break;
        default:                    xassertion(xtrue, "");                  break;
    }

    xlogfunction_end("%s(...) => %p", __func__, ret);

    return ret;
}

/**
 * @fn          extern xstream * xstreamrem(xstream * o)
 * @brief       스트림 객체의 소멸자 입니다.
 * @details
 * 
 * @param       o | xstream * | in | 스트립 객체 |
 * 
 * @return      | xstream * | 항상 널을 리턴합니다. |
 * 
 * @see         xstream
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xstream * xstreamrem(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xstream * ret = (o ? o->rem(o) : xnil);

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xbyte * xstreamback(xstream * o)
 * @brief       새로운 데이터를 삽입할 수 있는 스트림 메모리 주소를 리턴합니다.
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xbyte * | 메모리 주소 |
 * 
 * @see         xstream
 *              xbyte
 *              xstreamtype_buffer
 *              xstreambuffer
 *              xstreambuffer_back
 */
extern xbyte * xstreamback(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xbyte * ret = xnil;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffer_back((xstreambuffer *) o); break;
        default:                 xassertion(xtrue, "");                         break;
    }

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xbyte * xstreamfront(xstream * o)
 * @brief       스트림 객체에 저장된 데이터의 메모리 주소 값을 리턴합니다.
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xbyte * | 데이터의 메모리 주소 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambuffer_front
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xbyte * xstreamfront(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xbyte * ret = xnil;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffer_front((xstreambuffer *) o);    break;
        default:                 xassertion(xtrue, "");                             break;
    }

    xlogfunction_end("%s(...) => %p", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreamremain(xstream * o)
 * @brief       스트림 객체의 새로운 데이터를 담을 수 있는 메모리 공간의 크기를 리턴합니다.
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xuint64 | 새로운 데이터를 삽입할 수 있는 크기 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambuffer_remain
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreamremain(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffer_remain((xstreambuffer *) o);   break;
        default:                 xassertion(xtrue, "");                             break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreamlen(xstream * o)
 * @brief       스트림 객체의 데이터 크기
 * @details     
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xuint64 | 스트림 객체에 저장된 데이터의 크기 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambuffer_len
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreamlen(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffer_len((xstreambuffer *) o);  break;
        default:                 xassertion(xtrue, "");                         break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);

    return ret;
}

/**
 * @fn          extern xuint64 xstreamcapacity_set(xstream * o, xuint64 v)
 * @brief       스트림 객체의 저장 공간의 크기를 설정합니다.
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      v | xuint64   | in | 스트림 객체의 저장 공간의 크기 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambuffercapacity_set
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreamcapacity_set(xstream * o, xuint64 v)
{
    xlogfunction_start("%s(%p, %lu)", __func__, o, v);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffercapacity_set((xstreambuffer *) o, v);   break;
        default:                 xassertion(xtrue, "");                                     break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);

    return ret;
}

/**
 * @fn          extern xuint64 xstreamcapacity_get(xstream * o)
 * @brief       스트림 객체의 저장 공간의 크기
 * @details     
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xuint64 | 스트림 객체의 수용 공간의 크기 |
 */
extern xuint64 xstreamcapacity_get(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffercapacity_get((xstreambuffer *) o);  break;
        default:                 xassertion(xtrue, "");                                 break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreamsize_set(xstream * o, xuint64 n)
 * @brief       스트림 객체의 데이터 사용 크기를 리턴합니다.
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @param       n | xuint64   | in | 변경하고자 하는 스트림 객체의 사이즈 |
 * 
 * @return      | xuint64 | 변경된 사이즈 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreamsize_set(xstream * o, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, o, n);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffersize_set((xstreambuffer *) o, n);   break;
        default:                 xassertion(xtrue, "");                                 break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreamsize_get(xstream * o)
 * @brief       스트림 객체의 사용중인 메모리 공간의 크기
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xuint64 | 스트림 객체의 메모리 사용 크기 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreamsize_get(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffersize_get((xstreambuffer *) o);  break;
        default:                 xassertion(xtrue, "");                             break;
    }
    
    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreampos_set(xstream * o, xuint64 n)
 * @brief       스트림 객체에서 사용된 데이터의 인덱스
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @param       n | xuint64   | in | 설정하고자 하는 인덱스 |
 * 
 * @return      | xuint64 | 설정된 인덱스 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambufferpos_set
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreampos_set(xstream * o, xuint64 n)
{
    xlogfunction_start("%s(%p, %lu)", __func__, o, n);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambufferpos_set((xstreambuffer *) o, n);    break;
        default:                 xassertion(xtrue, "");                                 break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreampos_get(xstream * o)
 * @brief       스트림 객체의 사용한 데이터 인덱스
 * @details
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @return      | xuint64 | 스트림 객체의 사용한 데이터 인덱스 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambufferpos_get
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreampos_get(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");

    xuint64 ret = 0;

    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambufferpos_get((xstreambuffer *) o);   break;
        default:                 xassertion(xtrue, "");                             break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

/**
 * @fn          extern xuint64 xstreamadjust(xstream * o, xint32 force)
 * @brief       스트림 객체를 보정합니다.
 * @details     메모리 공간 최적화를 수행합니다.
 * 
 * @param       o | xstream * | in | 스트림 객체 |
 * @param       force | xint32 | in | 강제적 최적화 플래그 |
 * 
 * @return      | xuint64 | 사용할 수 있는 데이터 공간의 크기 |
 * 
 * @see         xstream
 *              xstreamtype_buffer
 *              xstreambuffer_adjust
 *              xstreambuffer
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xuint64 xstreamadjust(xstream * o, xint32 force)
{
    xlogfunction_start("%s(%p, %d)", __func__, o, force);

    xassertion(o == xnil, "");
    
    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffer_adjust((xstreambuffer *) o, force);    break;
        default:                 xassertion(xtrue, "");                                     break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

extern xuint64 xstreampush(xstream * o, const xbyte * data, xuint64 len)
{
    xlogfunction_start("%s(%p, $p, %lu)", __func__, o, data, len);

    xassertion(o == xnil, "");

    xuint64 ret = 0;
    switch(o->type)
    {
        case xstreamtype_buffer: ret = xstreambuffer_push((xstreambuffer *) o, data, len);  break;
        default:                 xassertion(xtrue, "");                                     break;
    }

    xlogfunction_end("%s(...) => %lu", __func__, ret);
    return ret;
}

extern void xstreamclear(xstream * o)
{
    xlogfunction_start("%s(%p)", __func__, o);

    xassertion(o == xnil, "");
    
    if(o)
    {
        switch(o->type)
        {
            case xstreamtype_buffer: xstreambuffer_clear((xstreambuffer *) o);  break;
        }
    }

    xlogfunction_end("%s(...)", __func__);
}

extern xstream * xstreamgen_str(const char * s)
{
    xstreambuffer * stream = xstreambuffer_new();
    xstreambuffer_push(stream, s, strlen(s));
}
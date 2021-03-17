/**
 * @file        x/std.h
 * @brief       표준 라이브러리의 헤더입니다.
 * @details     이 라이브러리의 가장 기본적으로 사용되는 타입, 함수, 매크로 등을 정의한 파일입니다.
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 * 
 * @todo        클래스 다이터그램 업데이터
 */
#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#include <x/log.h>

#define xinvalid            (-1)                /**!< 유효하지 않은 값을 나타냅니다. 특히 디스크립터가 유요하지 않음을 나타냅니다. */
#define xsuccess            (0)                 /**!< 어떤 프로세스의 수행이 성공하였음을 나타냅니다. */
#define xfail               (-1)                /**!< 어떤 프로세서의 수행이 실패하였음을 나타냅니다. */
#define xnil                ((void *) 0)        /**!< 널을 의미합니다. */
#define xtrue               (1)                 /**!< 참을 의미합니다. */
#define xfalse              (0)                 /**!< 거짓을 의미합니다. */

/**
 * @def         xvalueof(o)
 * @brief       주소값 않에 저장된 값을 리턴합니다.
 * @details
 * 
 * @param       o | ... | in | 변수 |
 * @return      | ... | 저장된 데이터를 리턴합니다. |
 */
#define xvalueof(o)         (*(o))

/**
 * @def         xaddressof(o)
 * @brief       변수의 주소값을 리턴합니다.
 * @details
 * 
 * @param       o | ... | in | 변수 |
 * 
 * @return      | xobject | 객체의 주소 값 |
 */
#define xaddressof(o)       (&(o))

typedef __INT8_TYPE__       xint8;              /**!< 8 비트 정수형입니다. */
typedef __INT16_TYPE__      xint16;             /**!< 16 비트 정수형입니다. */
typedef __INT32_TYPE__      xint32;             /**!< 32 비트 정수형입니다.  */
typedef __INT64_TYPE__      xint64;             /**!< 64 비트 정수형입니디. */
typedef __UINT8_TYPE__      xuint8;             /**!< 8 비트 양의 정수형입니다. */
typedef __UINT16_TYPE__     xuint16;            /**!< 16 비트 양의 정수형입니다. */
typedef __UINT32_TYPE__     xuint32;            /**!< 32 비트 양의 정수형입니다. */
typedef __UINT64_TYPE__     xuint64;            /**!< 64 비트 양의 정수형입니다. */
typedef unsigned char       xbyte;              /**!< 바이트 타입 */

typedef void *              xhandle;            /**!< 핸들 타입입니다. */
typedef void *              xobject;            /**!< 객체 타입입니다. */

union xval;

typedef union xval          xval;

typedef void (*xvalfunc)(xval *);

#define xvalinteger32(v)        (xval) { .i32 = v }
#define xvalinteger64(v)        (xval) { .i64 = v }
#define xvalunsigned32(v)       (xval) { .u32 = v }
#define xvalunsigned64(v)       (xval) { .u64 = v }
#define xvalobject(v)           (xval) { .p = v }

union xval
{
    xint32 i32;
    xuint32 u32;
    xint64 i64;
    xuint64 u64;
    void * p;
};

/**
 * @def         xcheck(condition, format, ...)
 * @brief       디버그를 위한 함수로 컨디션에 따라서 특정 포맷 형태로 콘솔에 출력합니다.
 * @details     
 * 
 * @param       condition | boolean        | in | 조건 |
 * @param       format    | const char *   | in | 출력할 포맷 문자열 |
 * @param       ...       | parameter list | in | 파라미터 리스트 |
 * 
 * @see         printf
 *              xthreadid
 *              __FILE__
 *              __LINE__
 *              __func__
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 * 
 * @todo        로그 패키지 업데이트
 *              
 *                  1. 파일 디스크립터 함수를 통하여 현재 로그 파일을 남기기 위한 파일 혹은 콘솔의 디스크립터를 입력 또는 선택할 수 있도록 해야 합니다.
 * 
 */
#define xcheck(condition, format, ...) do {                 \
    if(condition) {                                         \
        xlogcheck(#condition " " format, ##__VA_ARGS__);    \
    }                                                       \
} while(0)

#define xdebugonly(code) do { } while(0)

/**
 * @def         xassertion(condition, format, ...)
 * @brief       반드시 거짓이어야 하는 어썰션의 표현식입니다.
 * @details     ASSERTION 조건이 참이면 프로그램이 종료됩니다.
 *              
 * @param       condition | bool | in | 조건 |
 * @param       format    | const char * | in | 포맷 문자열 |
 * @param       ...       | -            | in | 파라미터 리스트 |
 * 
 * @see         printf
 *              xthreadid
 *              __FILE__
 *              __LINE__
 *              __func__
 *              exit
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 */
#define xassertion(condition, format, ...) do {                 \
    if(condition) {                                             \
        xlogassertion(#condition " " format, ##__VA_ARGS__);    \
        exit(xinvalid);                                         \
    }                                                           \
} while(0)

/**
 * @def         xobjectof(o)
 * @brief       강제적으로 객체형으로 변환합니다.
 * 
 * @param       o | - | in | 변수 |
 * 
 * @return      | xobject | 강제적으로 형변환된 객체 |
 */
#define        xobjectof(o)     ((void *) o)
extern xobject xobjectdup(const void * data, xuint64 size);
extern xobject xobjectnew(xuint64 size);
extern xobject xobjectrem(xobject o);

extern void xrandominit(void);
extern xint64 xrandomget(void);
extern xuint64 xrandomunsigned64(xuint64 max);
extern xint64 xrandominteger64(xuint64 max);

#endif // __NOVEMBERIZING_X__STD__H__

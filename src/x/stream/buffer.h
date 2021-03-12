#ifndef   __NOVEMBERIZING_X__STREAM__BUFFER__H__
#define   __NOVEMBERIZING_X__STREAM__BUFFER__H__

#include <x/stream.h>

struct xstreambuffer;

typedef struct xstreambuffer xstreambuffer;                             /**!< 스트림 버퍼 객체 타입 */

typedef xstreambuffer * (*xstreambufferdestructor)(xstreambuffer *);    /**!< 스트림 버퍼 객체의 소멸자 */

/**
 * @struct      xstreambuffer
 * @brief       스트림 버퍼 객체
 * @details     선형 메모리 공간으로 구현한 바이트 버퍼 스트림
 * 
 */
struct xstreambuffer
{
    xuint32                 type;       /**!< 스트림 타입 */
    xstreambufferdestructor rem;        /**!< 바이트 버퍼 스트림 소멸자  */
    xbyte *                 buffer;     /**!< 선형 메모리 공간  */
    xuint64                 position;   /**!< 사용한 데이터의 인덱스 */
    xuint64                 size;       /**!< 사용한 데이터의 크기 */
    xuint64                 capacity;   /**!< 전체 메모리 공간의 크기 */
};

extern xstreambuffer * xstreambuffer_new(void);
extern xstreambuffer * xstreambuffer_rem(xstreambuffer * o);

extern xbyte * xstreambuffer_back(xstreambuffer * o);
extern xbyte * xstreambuffer_front(xstreambuffer * o);
extern xuint64 xstreambuffer_remain(xstreambuffer * o);
extern xuint64 xstreambuffer_len(xstreambuffer * o);

extern xuint64 xstreambuffercapacity_set(xstreambuffer * o, xuint64 v);
extern xuint64 xstreambuffercapacity_get(xstreambuffer * o);
extern xuint64 xstreambuffersize_set(xstreambuffer * o, xuint64 n);
extern xuint64 xstreambuffersize_get(xstreambuffer * o);
extern xuint64 xstreambufferpos_set(xstreambuffer * o, xuint64 n);
extern xuint64 xstreambufferpos_get(xstreambuffer * o);

extern xuint64 xstreambuffer_adjust(xstreambuffer * o, xint32 force);

extern xuint64 xstreambuffer_push(xstreambuffer * o, const xbyte * data, xuint64 len);
extern void xstreambuffer_clear(xstreambuffer * o);

#endif // __NOVEMBERIZING_X__STREAM__BUFFER__H__

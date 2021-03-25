#ifndef   __NOVEMBERIZING_X__STRING__FORMAT__H__
#define   __NOVEMBERIZING_X__STRING__FORMAT__H__

/**
 * TODO: VA_LIST 를 사용하기 위해서 임시적으로 STD 헤더 파일을 참조하였다.
 *       하지만, STD 헤더는 라이브러리 헤더에 참조하고 싶지 않다.
 *       어떻게 하면 STDARG 를 사용하지 않고  VA_LIST 를 사용할까?
 * 
 * 
 */
#include <stdarg.h>

#include <x/string.h>

typedef char * (*xstringserializer)(char * s, xuint64 * index, xuint64 * capacity, xint32, const char *, va_list);

extern char * xsprintf(char * s, xuint64 * index, xuint64 * capacity, const char * format, ...);
extern char * xvsprintf(char * s, xuint64 * index, xuint64 * capacity, const char * format, va_list ap);

extern char * xstringformat(char * s, xuint64 * index, xuint64 * capacity, xstringserializer serializer, const char * format, ...);
extern char * xstringformatv(char * s, xuint64 * index, xuint64 * capacity, xstringserializer serializer, const char * format, va_list ap);


extern char * xstringformatserialize(char * s, xuint64 * index, xuint64 * capacity, xint32 specifier, const char * format, va_list ap);
// typedef xstring * (*xstringserializer)(xstring *, xint32, const char *, va_list);

// extern xstring * xsprintf(xstring * o, const char * format, ...);
// extern xstring * xvsprtinf(xstring * o, const char * format, va_list ap);

// extern xstring * xstringformat(xstring * o, xstringserializer serializer, const char * format, ...);
// extern xstring * xstringformatv(xstring * o, xstringserializer serializer, const char * format, va_list ap);

#endif // __NOVEMBERIZING_X__STRING__FORMAT__H__

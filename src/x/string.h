#ifndef   __NOVEMBERIZING_X__STRING__H__
#define   __NOVEMBERIZING_X__STRING__H__

#include <x/std.h>

extern char * xstringdup(const char * source, xuint64 len);
extern char * xstringcpy(char * o, xuint64 * index, xuint64 * capacity, const char * source);
extern char * xstringncpy(char * o, xuint64 * index, xuint64 * capacity, const char * source, xuint64 n);

extern char * xstringline_next(char * o, xuint64 * index, xuint64 limit);
extern char * xstringstr_next(char * o, xuint64 * index, xuint64 limit, const char * s);
extern char * xstringchr_next(char * o, xuint64 * index, xuint64 limit, int c);

extern xuint64 xstringwhitespace_split(char ** strings, const char * s, xuint64 limit);

extern char * xstringcapacity_set(char * s, xuint64 * index, xuint64 * capacity, xuint32 n);

extern xuint64 xstringtouint64(char * s, xuint64 limit);
extern xint64 xstringtoint64(char * s, xuint64 limit);

#endif // __NOVEMBERIZING_X__STRING__H__

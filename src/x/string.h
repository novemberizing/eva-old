#ifndef   __NOVEMBERIZING_X__STRING__H__
#define   __NOVEMBERIZING_X__STRING__H__

#include <x/std.h>

extern char * xstringcpy(char * o, xuint64 * index, xuint64 * capacity, const char * source);
extern char * xstringncpy(char * o, xuint64 * index, xuint64 * capacity, const char * source, xuint64 n);

#endif // __NOVEMBERIZING_X__STRING__H__

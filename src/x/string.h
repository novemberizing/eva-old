#ifndef   __NOVEMBERIZING_X__STRING__H__
#define   __NOVEMBERIZING_X__STRING__H__

#include <x/std.h>

#define xinteger32str(s)        *((xint32 *) s)

typedef void (*xstringfunc)(const char *, xuint64);

extern xint64 xinteger64from_str(const char * s);
extern xint32 xinteger32from_str(const char * s);

extern char * xstringto_lower(char * output, char * source);

extern char * xstringline_gen(char * output, const char * s);

extern const char * xstringline_get(const char * s, xstringfunc callback);

extern char ** xstringword_gen(char ** output, xuint64 * size, const char * s);

extern char * xstringline_dup(char * output, const char * s, const char * next);
extern char * xstringdup(char * output, const char * s, xuint64 n);

extern char * xstringcharcontinue_str(const char * s, const char * needle);
extern char * xstringchar_str(const char * s, const char * needle);
extern char * xchrchr_str(int c, const char * needle);
extern const char * xstringword_get(const char * s, xstringfunc callback);
extern char * xstringword_dup(char * output, const char * s, const char * next);
extern char ** xstringword_split(char ** output, xuint64 * n, const char * line);

#endif // __NOVEMBERIZING_X__STRING__H__

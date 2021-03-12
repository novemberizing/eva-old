#ifndef   __NOVEMBERIZING_X__STRING__H__
#define   __NOVEMBERIZING_X__STRING__H__

#include <x/std.h>

typedef void (*xstringfunc)(const char *, xuint64);

extern const char * xstringline_get(const char * s, xstringfunc callback);

extern char ** xstringword_gen(char ** output, xuint64 * size, const char * s);

extern char * xstringline_dup(char * output, const char * s, const char * next);
extern char * xstringdup(char * output, const char * s, xuint64 n);

extern char * xstringcharcontinue_str(const char * s, const char * needle);
extern char * xstringchar_str(const char * s, const char * needle);
extern char * xchrchr_str(int c, const char * needle);
extern const char * xstringword_get(const char * s, xstringfunc callback);
extern char * xstringword_dup(char * output, const char * s, const char * next);


#endif // __NOVEMBERIZING_X__STRING__H__

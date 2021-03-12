#ifndef   __NOVEMBERIZING_X__LOG__H__
#define   __NOVEMBERIZING_X__LOG__H__

#define xlogtype_verbose        (0x00000001u)
#define xlogtype_debug          (0x00000002u)
#define xlogtype_information    (0x00000004u)
#define xlogtype_notice         (0x00000008u)
#define xlogtype_caution        (0x00000010u)
#define xlogtype_warning        (0x00000020u)
#define xlogtype_error          (0x00000040u)
#define xlogtype_critical       (0x00000080u)
#define xlogtype_assertion      (0x00000100u)
#define xlogtype_check          (0x00000200u)
#define xlogtype_todo           (0x00000400u)
#define xlogtype_function_start (0x00000800u)
#define xlogtype_function_end   (0x00001000u)

#define xlogtype_all            (0xFFFFFFFFu)

extern void xlogpath_set(const char * path);
extern unsigned int xlogmask_get(void);
extern void xlogmask_set(unsigned int value);

extern void xlogout(unsigned int type, const char * file, int line, const char * func, const char * format, ...);

#define xlogfunction_start(format, ...) do {    \
    xlogout(xlogtype_function_start,            \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogfunction_end(format, ...) do {      \
    xlogout(xlogtype_function_end,              \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogverbose(format, ...) do {           \
    xlogout(xlogtype_verbose,                   \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogdebug(format, ...) do {             \
    xlogout(xlogtype_debug,                     \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xloginformation(format, ...) do {       \
    xlogout(xlogtype_information,               \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlognotice(format, ...) do {            \
    xlogout(xlogtype_notice,                    \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogcaution(format, ...) do {           \
    xlogout(xlogtype_caution,                   \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogwarning(format, ...) do {           \
    xlogout(xlogtype_warning,                   \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogerror(format, ...) do {             \
    xlogout(xlogtype_error,                     \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogcritical(format, ...) do {          \
    xlogout(xlogtype_critical,                  \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogassertion(format, ...) do {         \
    xlogout(xlogtype_assertion,                 \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogcheck(format, ...) do {             \
    xlogout(xlogtype_check,                     \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#define xlogtodo(format, ...) do {              \
    xlogout(xlogtype_todo,                      \
            __FILE__,                           \
            __LINE__,                           \
            __func__,                           \
            format,                             \
            ##__VA_ARGS__);                     \
} while(0)

#endif // __NOVEMBERIZING_X__LOG__H__

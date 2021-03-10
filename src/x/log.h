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

extern int xlogf(unsigned int type);
extern void xlogterm(void);
extern unsigned int xlogmask_get(void);
extern void xlogmask_set(unsigned int v);

#define xlogverbose(format, ...) do {                       \
    if(xlogmask_get() & xlogtype_verbose) {                 \
        dprintf(xlogf(), "[verbose] %s:%d %s(...) %ld "     \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogdebug(format, ...) do {                         \
    if(xlogmask_get() & xlogtype_debug) {                   \
        dprintf(xlogf(), "[debug] %s:%d %s(...) %ld "       \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_information(format, ...) do {              \
    if(xlogmask_get() & xlogtype_information) {             \
        dprintf(xlogf(), "[information] %s:%d %s(...) %ld " \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_notice(format, ...) do {                   \
    if(xlogmask_get() & xlogtype_notice) {                  \
        dprintf(xlogf(), "[notice] %s:%d %s(...) %ld "      \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_caution(format, ...) do {                  \
    if(xlogmask_get() & xlogtype_caution) {                 \
        dprintf(xlogf(), "[caution] %s:%d %s(...) %ld "     \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_warning(format, ...) do {                  \
    if(xlogmask_get() & xlogtype_warning) {                 \
        dprintf(xlogf(), "[warning] %s:%d %s(...) %ld "     \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_error(format, ...) do {                    \
    if(xlogmask_get() & xlogtype_error) {                   \
        dprintf(xlogf(), "[error] %s:%d %s(...) %ld "       \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_critical(format, ...) do {                 \
    if(xlogmask_get() & xlogtype_critical) {                \
        dprintf(xlogf(), "[critical] %s:%d %s(...) %ld "    \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_assertion(format, ...) do {                \
    if(xlogmask_get() & xlogtype_assertion) {               \
        dprintf(xlogf(), "[assertion] %s:%d %s(...) %ld "   \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_check(format, ...) do {                    \
    if(xlogmask_get() & xlogtype_check) {                   \
        dprintf(xlogf(), "[check] %s:%d %s(...) %ld "       \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#define xlogtype_todo(format, ...) do {                     \
    if(xlogmask_get() & xlogtype_todo) {                    \
        dprintf(xlogf(), "[todo] %s:%d %s(...) %ld "        \
                         format "\n",                       \
                         __FILE__,                          \
                         __LINE__,                          \
                         __func__,                          \
                         xthreadid(),                       \
                         ##__VA_ARGS__);                    \
    }                                                       \
} while(0)

#endif // __NOVEMBERIZING_X__LOG__H__

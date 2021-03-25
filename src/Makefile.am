# SUBDIRS = example eva

AM_CFLAGS = -I$(top_srcdir)/src
ACLOCAL_AMFLAGS = -I m4

lib_LIBRARIES = libnovemberizing.a

# TODO: 디스크립터 이벤트 제네레이터를 OS 에 알맞는 소스를 링크하도록 한다.
libnovemberizing_a_SOURCES = x/std.c                                          \
                             x/log.c                                          \
                             x/string.c                                       \
                             x/string/format.c                                \
                             x/dictionary.c                                   \
                             x/array.c                                        \
                             x/list.c                                         \
                             x/stack.c                                        \
                             x/queue.c                                        \
                             x/set.c                                          \
                             x/map.c                                          \
                             x/object.c                                       \
                             x/exception.c                                    \
                             x/thread.c                                       \
                             x/thread/posix.c                                 \
                             x/sync.c                                         \
                             x/sync/posix/mutex.c                             \
                             x/stream.c                                       \
                             x/stream/buffer.c                                \
                             x/command.c                                      \
                             x/command/string.c                               \
                             x/event/queue.c                                  \
                             x/event/processor.c                              \
                             x/event/subscription.c                           \
                             x/event/engine.c                                 \
                             x/event/processor/pool.c                         \
                             x/event/processor/event.c                        \
                             x/event/generator/set.c                          \
                             x/descriptor.c                                   \
                             x/descriptor/status.c                            \
                             x/descriptor/event/avail.c                       \
                             x/descriptor/event/type.c                        \
                             x/descriptor/event/dispatch.c                    \
                             x/descriptor/event/generator.c                   \
                             x/descriptor/event/generator/epoll.c             \
                             x/descriptor/event/generator/subscription/list.c \
                             x/console.c                                      \
                             x/console/descriptor/event/processor/in.c        \
                             x/console/descriptor/event/processor/out.c       \
                             x/socket.c                                       \
                             x/socket/handle.c                                \
                             x/server.c                                       \
                             x/server/socket.c                                \
                             x/session.c                                      \
                             x/session/socket.c                               \
                             x/client.c                                       \
                             x/client/pool.c                                  \
                             x/client/pool/list.c                             \
                             x/client/socket.c                                \
                             x/client/socket/event/avail.c                    \
                             x/client/socket/event/process/tcp.c              \
                             x/eva.c                                          \
                             x/eva/cli.c                                      \
                             x/eva/extension/echo.c



LIBS = libnovemberizing.a                                                    \
       -lpthread

noinst_PROGRAMS = example-helloworld                                         \
                  example-client-redis                                       \
                  example-client-pool                                        \
                  example-string-simple                                      \
                  example-string-format

example_helloworld_SOURCES    = example/helloworld.c
example_helloworld_LDADD      = $(LIBS)

example_client_redis_SOURCES  = example/client/redis.c
example_client_redis_LDADD    = $(LIBS)

example_client_pool_SOURCES   = example/client/pool.c
example_client_pool_LDADD     = $(LIBS)

example_string_format_SOURCES = example/string/format.c
example_string_format_LDADD   = $(LIBS)

example_string_simple_SOURCES = example/string/simple.c
example_string_simple_LDADD   = $(LIBS)

nobase_include_HEADERS = x/std.h                \
                         x/thread.h             \
                         x/sync.h               \
                         x/stream.h
                         

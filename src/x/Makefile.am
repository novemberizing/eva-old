AM_CFLAGS = -I$(top_srcdir)/src
ACLOCAL_AMFLAGS = -I m4

lib_LIBRARIES = libnovemberizing.a

# TODO: 디스크립터 이벤트 제네레이터를 OS 에 알맞는 소스를 링크하도록 한다.
libnovemberizing_a_SOURCES = std.c                                          \
                             object.c                                       \
                             exception.c                                    \
                             thread.c                                       \
                             thread/posix.c                                 \
                             sync.c                                         \
                             sync/posix/mutex.c                             \
                             stream.c                                       \
                             stream/buffer.c                                \
                             event/queue.c                                  \
                             event/processor.c                              \
                             event/subscription.c                           \
                             event/engine.c                                 \
                             event/processor/pool.c                         \
                             event/processor/event.c                        \
                             event/generator/set.c                          \
                             descriptor.c                                   \
                             descriptor/event/generator.c                   \
                             descriptor/event/generator/epoll.c             \
                             descriptor/event/generator/subscription/list.c \
                             console.c                                      \
                             socket.c                                       \
                             server.c                                       \
                             server/socket.c                                \
                             session.c                                      \
                             session/socket.c


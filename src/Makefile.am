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
                             x/time.c                                         \
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
                             x/server/socket/event/avail.c                    \
                             x/server/socket/event/process/tcp.c              \
                             x/server/extension/echo.c                        \
                             x/session.c                                      \
                             x/session/socket.c                               \
                             x/session/socket/event/avail.c                   \
                             x/session/socket/event/process/tcp.c             \
                             x/client.c                                       \
                             x/client/pool.c                                  \
                             x/client/pool/list.c                             \
                             x/client/socket.c                                \
                             x/client/socket/event/avail.c                    \
                             x/client/socket/event/process/tcp.c              \
                             x/extension/redis.c                              \
                             x/extension/redis/object.c                       \
                             x/extension/redis/object/string.c                \
                             x/extension/redis/object/error.c                 \
                             x/extension/redis/object/integer.c               \
                             x/extension/redis/object/bulk.c                  \
                             x/extension/redis/object/array.c                 \
                             x/extension/redis/client.c                       \
                             x/extension/redis/req.c                          \
                             x/extension/redis/res.c                          \
                             x/extension/echo/req.c                           \
                             x/extension/echo/res.c                           \
                             x/eva.c                                          \
                             x/eva/cli.c



LIBS = libnovemberizing.a                                                    \
       -lpthread

noinst_PROGRAMS = example-helloworld                                         \
                  example-client-redis                                       \
                  example-client-pool                                        \
                  example-client-single                                      \
                  example-string-simple                                      \
                  example-string-format                                      \
                  example-string-uint64                                      \
                  example-string-new                                         \
                  example-console-engine                                     \
                  example-redis-ping                                         \
                  example-redis-protocol                                     \
                  example-redis-set                                          \
                  example-redis-client                                       \
                  example-redis-req                                          \
                  example-server-simple                                      \
                  benchmark-server                                           \
                  benchmark-client                                           \
                  benchmark-string                                           \
                  benchmark-format

benchmark_format_SOURCES       = example/benchmark/format.c
benchmark_format_LDADD         = $(LIBS)

benchmark_string_SOURCES       = example/benchmark/string.c
benchmark_string_LDADD         = $(LIBS)

benchmark_server_SOURCES       = example/benchmark/server.c
benchmark_server_LDADD         = $(LIBS)

benchmark_client_SOURCES       = example/benchmark/client.c
benchmark_client_LDADD         = $(LIBS)

example_helloworld_SOURCES     = example/helloworld.c
example_helloworld_LDADD       = $(LIBS)

example_client_redis_SOURCES   = example/client/redis.c
example_client_redis_LDADD     = $(LIBS)

example_client_pool_SOURCES    = example/client/pool.c
example_client_pool_LDADD      = $(LIBS)

example_client_single_SOURCES  = example/client/single.c
example_client_single_LDADD    = $(LIBS)

example_string_format_SOURCES  = example/string/format.c
example_string_format_LDADD    = $(LIBS)

example_string_simple_SOURCES  = example/string/simple.c
example_string_simple_LDADD    = $(LIBS)

example_string_uint64_SOURCES  = example/string/uint64.c
example_string_uint64_LDADD    = $(LIBS)

example_string_new_SOURCES     = example/string/new.c
example_string_new_LDADD       = $(LIBS)

example_console_engine_SOURCES = example/console/engine.c
example_console_engine_LDADD   = $(LIBS)

example_redis_ping_SOURCES     = example/redis/ping.c
example_redis_ping_LDADD       = $(LIBS)

example_redis_protocol_SOURCES = example/redis/protocol.c
example_redis_protocol_LDADD   = $(LIBS)

example_redis_set_SOURCES      = example/redis/set.c
example_redis_set_LDADD        = $(LIBS)

example_redis_req_SOURCES      = example/redis/req.c
example_redis_req_LDADD        = $(LIBS)

example_redis_client_SOURCES   = example/redis/client.c
example_redis_client_LDADD     = $(LIBS)

example_server_simple_SOURCES  = example/server/simple.c
example_server_simple_LDADD    = $(LIBS)

nobase_include_HEADERS = x/std.h                \
                         x/thread.h             \
                         x/sync.h               \
                         x/stream.h
                         

# SUBDIRS = example eva

AM_CFLAGS = -I$(top_srcdir)/src
ACLOCAL_AMFLAGS = -I m4

lib_LIBRARIES = libnovemberizing.a

# TODO: 디스크립터 이벤트 제네레이터를 OS 에 알맞는 소스를 링크하도록 한다.
libnovemberizing_a_SOURCES = x/std.c                                          \
                             x/log.c                                          \
                             x/string.c                                       \
                             x/object.c                                       \
                             x/exception.c                                    \
                             x/thread.c                                       \
                             x/thread/posix.c                                 \
                             x/sync.c                                         \
                             x/sync/posix/mutex.c                             \
                             x/stream.c                                       \
                             x/stream/buffer.c                                \
                             x/event/queue.c                                  \
                             x/event/processor.c                              \
                             x/event/subscription.c                           \
                             x/event/engine.c                                 \
                             x/event/processor/pool.c                         \
                             x/event/processor/event.c                        \
                             x/event/generator/set.c                          \
                             x/descriptor.c                                   \
                             x/descriptor/event/generator.c                   \
                             x/descriptor/event/generator/epoll.c             \
                             x/descriptor/event/generator/subscription/list.c \
                             x/console.c                                      \
                             x/socket.c                                       \
                             x/server.c                                       \
                             x/server/socket.c                                \
                             x/session.c                                      \
                             x/session/socket.c                               \
                             x/client.c                                       \
                             x/client/socket.c



LIBS = libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = benchmark-log                 \
                  example-client-simple         \
                  example-console-io            \
                  example-event-engine          \
                  example-event-console         \
                  example-event-server          \
                  example-string-api            \
                  example-command-string        \
                  evad

benchmark_log_SOURCES           = example/benchmark/log.c
benchmark_log_LDADD             = $(LIBS)

example_client_simple_SOURCES   = example/client/simple.c
example_client_simple_LDADD     = $(LIBS)

example_console_io_SOURCES      = example/console/io.c
example_console_io_LDADD        = $(LIBS)

example_event_engine_SOURCES    = example/event/engine.c
example_event_engine_LDADD      = $(LIBS)

example_event_console_SOURCES   = example/event/console.c
example_event_console_LDADD     = $(LIBS)

example_event_server_SOURCES    = example/event/server.c
example_event_server_LDADD      = $(LIBS)

example_string_api_SOURCES      = example/string/api.c
example_string_api_LDADD        = $(LIBS)

example_command_string_SOURCES  = example/command/string.c
example_command_string_LDADD    = $(LIBS)

evad_SOURCES                    = eva/eva.c        \
                                  eva/console.c    \
                                  eva/echo.c

evad_LDADD    = $(LIBS)

nobase_include_HEADERS = x/std.h                \
                         x/thread.h             \
                         x/sync.h               \
                         x/stream.h
                         

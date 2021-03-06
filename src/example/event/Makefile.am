AM_CFLAGS = -I$(top_srcdir)/src

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = example-event-engine  \
                  example-event-console \
                  example-event-server

example_event_engine_SOURCES  = engine.c
example_event_engine_LDADD    = $(LIBS)

example_event_console_SOURCES = console.c
example_event_console_LDADD   = $(LIBS)

example_event_server_SOURCES = server.c
example_event_server_LDADD   = $(LIBS)

AM_CFLAGS = -I$(top_srcdir)/src

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = example-console-io

example_console_io_SOURCES  = io.c
example_console_io_LDADD    = $(LIBS)

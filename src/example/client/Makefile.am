AM_CFLAGS = -I$(top_srcdir)/src

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = example-client-simple

example_client_simple_SOURCES  = simple.c
example_client_simple_LDADD    = $(LIBS)

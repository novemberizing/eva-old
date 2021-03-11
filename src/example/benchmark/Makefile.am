AM_CFLAGS = -I$(top_srcdir)/src

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = benchmark-log

benchmark_log_SOURCES  = log.c
benchmark_log_LDADD    = $(LIBS)

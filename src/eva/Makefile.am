AM_CFLAGS = -I$(top_srcdir)/src

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = eva

eva_SOURCES  = eva.c \
               echo.c

eva_LDADD    = $(LIBS)

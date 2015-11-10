# Copyright (c) 2015 SICOM Systems Inc (zboszormenyi@sicom.com)

lib_LTLIBRARIES = libphpscrew.la

AM_CPPFLAGS = -I$(top_srcdir)/include $(ZLIB_CFLAGS)

libphpscrew_la_SOURCES = zencode.c screw.c
libphpscrew_la_LIBADD = $(ZLIB_LIBS)
libphpscrew_la_LDFLAGS = $(LDFLAGS) -shared -version-info $(LIBPHPSCREW_CURRENT):$(LIBPHPSCREW_REVISION):$(LIBPHPSCREW_AGE)

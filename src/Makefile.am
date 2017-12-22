AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_cstr.la

libvmod_cstr_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_cstr_la_SOURCES = \
	vmod_cstr.c

nodist_libvmod_cstr_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

vmod_cstr.lo: vcc_if.c vcc_if.h

vcc_if.c: vcc_if.h

vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_cstr.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_cstr.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc: libvmod_cstr.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_cstr.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_cstr.rst \
	$(builddir)/vmod_cstr.man.rst

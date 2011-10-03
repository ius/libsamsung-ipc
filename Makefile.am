NULL =

SUBDIRS = \
	samsung-ipc \
	include \
	tools \
	$(NULL)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = samsung-ipc-1.0.pc

EXTRA_DIST = \
	MAINTAINERS \
	samsung-ipc-1.0.pc \
	$(NULL)

vapidir = $(datadir)/vala/vapi

dist_vapi_DATA = \
	vapi/samsung-ipc-1.0.vapi \
	$(NULL)

MAINTAINERCLEANFILES = \
	aclocal.m4 compile config.guess config.sub \
	configure depcomp install-sh ltmain.sh     \
	Makefile.in missing config.h.in            \
	mkinstalldirs *~ \
	$(NULL)

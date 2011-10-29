NULL =

AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/samsung-ipc \
	$(OPENSSL_CFLAGS) \
	$(NULL)

if WANT_DEBUG
AM_CFLAGS += -ggdb -O0
endif

lib_LTLIBRARIES = \
	libsamsung-ipc.la \
	$(NULL)

libsamsung_ipc_la_SOURCES = \
	ipc.c \
	ipc_util.c \
	util.c \
	\
	misc.c \
	sec.c \
	gprs.c \
	call.c \
	net.c \
	$(NULL)

if WANT_PROTOCOL_VERISON_CRESPO
libsamsung_ipc_la_SOURCES += \
	device/crespo/crespo_ipc.c \
	device/crespo/crespo_nv_data.c \
	$(NULL)
endif

if WANT_PROTOCOL_VERISON_H1
libsamsung_ipc_la_SOURCES += \
	device/h1/h1_ipc.c \
	$(NULL)
endif

libsamsung_ipc_la_LIBADD = \
	$(OPENSSL_LIBS) \
	$(NULL)

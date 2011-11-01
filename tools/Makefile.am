NULL =

AM_CFLAGS = \
	-I$(top_srcdir)/include \
	$(NULL)

bin_PROGRAMS = modemctrl

modemctrl_SOURCES = \
	modemctrl.c \
	$(NULL)

if WANT_PROTOCOL_VERISON_CRESPO
AM_CFLAGS += -DDEVICE_CRESPO
endif

if WANT_PROTOCOL_VERISON_H1
AM_CFLAGS += -DDEVICE_H1
endif

modemctrl_LDADD = $(top_srcdir)/samsung-ipc/libsamsung-ipc.la
modemctrl_LDFLAGS =

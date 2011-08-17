CROSS_COMPILE ?= arm-none-linux-gnueabi-

all: lib test

lib:
	$(CROSS_COMPILE)gcc -Iinclude -shared radio.c hexdump.c -o libsamsung-ipc.so

test:
	$(CROSS_COMPILE)gcc -shared -Iinclude test.c -L. -lsamsung-ipc -lpthread -o ipc-test


CROSS_COMPILE ?= arm-none-linux-gnueabi-

all: lib test

lib:
	$(CROSS_COMPILE)gcc -Iinclude -shared radio.c hexdump.c -o libmsm-h1.so

test:
	$(CROSS_COMPILE)gcc -shared -Iinclude test.c -L. -lmsm-h1 -lpthread -o msm-test


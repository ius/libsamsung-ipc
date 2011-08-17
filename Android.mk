LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

libsamsung-ipc_files := \
	radio.c \
	util.c \
	hexdump.c \
	call.c \
	sim.c \
	sms.c \
	net.c \
	misc.c

LOCAL_MODULE := libsamsung-ipc
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := $(libsamsung-ipc_files)
include $(BUILD_STATIC_LIBRARY)


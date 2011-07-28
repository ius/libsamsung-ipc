LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

libmsm-h1_files := \
	radio.c \
	util.c \
	hexdump.c \
	call.c \
	sms.c \
	net.c \
	misc.c

LOCAL_MODULE := libmsm-h1
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := $(libmsm-h1_files)
include $(BUILD_STATIC_LIBRARY)


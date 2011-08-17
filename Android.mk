LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

libsamsung-ipc_files := \
	ipc.c \
	ipc_util.c \
	util.c \
	devices/$(TARGET_DEVICE)/ipc.c

LOCAL_MODULE := libsamsung-ipc
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := $(libsamsung-ipc_files)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := ipc-test
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libutils

LOCAL_CFLAGS := -DLOG_STDOUT
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := $(libsamsung-ipc_files) test.c

include $(BUILD_EXECUTABLE)


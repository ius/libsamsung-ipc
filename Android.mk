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

ifeq ($(TARGET_DEVICE),crespo)
       libsamsung-ipc_files += devices/$(TARGET_DEVICE)/nv_data.c
       LOCAL_CFLAGS += -Iexternal/openssl/include
       LOCAL_LDFLAGS += -lcrypto
endif

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := ipc-test
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libutils

LOCAL_CFLAGS := -DLOG_STDOUT
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := $(libsamsung-ipc_files) test.c

ifeq ($(TARGET_DEVICE),crespo)
       libsamsung-ipc_files += devices/$(TARGET_DEVICE)/nv_data.c
       LOCAL_CFLAGS += -Iexternal/openssl/include
       LOCAL_LDFLAGS += -lcrypto
endif

include $(BUILD_EXECUTABLE)


BUILD_IPC-MODEMCTRL := true
DEBUG := true

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libsamsung-ipc
LOCAL_MODULE_TAGS := optional

samsung-ipc_files := \
	samsung-ipc/ipc.c \
	samsung-ipc/ipc_util.c \
	samsung-ipc/util.c \
	samsung-ipc/gprs.c \
	samsung-ipc/misc.c \
	samsung-ipc/net.c \
	samsung-ipc/sec.c \
	samsung-ipc/device/$(TARGET_DEVICE)/$(TARGET_DEVICE)_ipc.c

ifeq ($(TARGET_DEVICE),crespo)
	device_files := samsung-ipc/device/$(TARGET_DEVICE)/$(TARGET_DEVICE)_nv_data.c
	LOCAL_CFLAGS += -Iexternal/openssl/include
	LOCAL_LDFLAGS += -lcrypto
	LOCAL_CFLAGS += -DDEVICE_CRESPO
endif

ifeq ($(TARGET_DEVICE),h1)
	LOCAL_CFLAGS += -DDEVICE_H1
endif

ifeq ($(DEBUG),true)
	LOCAL_CFLAGS += -DDEBUG
	LOCAL_CFLAGS += -DLOG_STDOUT
endif

LOCAL_SRC_FILES := $(samsung-ipc_files) $(device_files)

LOCAL_SHARED_LIBRARIES := libutils
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
	$(LOCAL_PATH)/samsung-ipc

include $(BUILD_STATIC_LIBRARY)

ifeq ($(BUILD_IPC-MODEMCTRL),true)

include $(CLEAR_VARS)

LOCAL_MODULE := ipc-modemctrl
LOCAL_MODULE_TAGS := optional

modemctrl_files := tools/modemctrl.c

ifeq ($(TARGET_DEVICE),crespo)
	LOCAL_CFLAGS += -DDEVICE_CRESPO
endif
ifeq ($(TARGET_DEVICE),h1)
	LOCAL_CFLAGS += -DDEVICE_H1
endif

LOCAL_SRC_FILES := $(modemctrl_files)

LOCAL_STATIC_LIBRARIES := libsamsung-ipc
LOCAL_SHARED_LIBRARIES := libutils
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

include $(BUILD_EXECUTABLE)

endif

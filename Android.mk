LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ipc-modemctrl
LOCAL_MODULE_TAGS := optional

samsung-ipc_files := \
	samsung-ipc/ipc.c \
	samsung-ipc/ipc_util.c \
	samsung-ipc/crespo_ipc.c \
	samsung-ipc/crespo_nv_data.c \
	samsung-ipc/util.c

modemctrl_files := tools/modemctrl.c

LOCAL_SRC_FILES := $(samsung-ipc_files) $(modemctrl_files)
LOCAL_SHARED_LIBRARIES := libutils
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
	$(LOCAL_PATH)/samsung-ipc
LOCAL_CFLAGS += -Iexternal/openssl/include
LOCAL_LDFLAGS += -lcrypto

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_EXECUTABLE)

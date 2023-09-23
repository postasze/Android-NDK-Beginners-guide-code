LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := com_packtpub_store_Store
LOCAL_SRC_FILES := com_packtpub_store_Store.cpp

include $(BUILD_SHARED_LIBRARY)

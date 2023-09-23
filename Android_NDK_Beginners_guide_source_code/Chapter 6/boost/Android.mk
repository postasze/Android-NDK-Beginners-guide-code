LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= boost_unit_test_framework
LOCAL_SRC_FILES:= android-$(TARGET_ARCH_ABI)/lib/libboost_unit_test_framework.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(PREBUILT_STATIC_LIBRARY)


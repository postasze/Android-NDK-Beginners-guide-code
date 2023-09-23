LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
LOCAL_MODULE := droidblaster
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2 -lOpenSLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue png box2d_static

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
LS_CPP_TEST=$(subst $(1)/,,$(wildcard $(1)/../test/*.cpp))
LOCAL_MODULE := droidblaster_test
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH)) \
    $(call LS_CPP_TEST,$(LOCAL_PATH))
LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2 -lOpenSLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue png box2d_static \
    libboost_unit_test_framework

include $(BUILD_EXECUTABLE)


$(call import-module,android/native_app_glue)
$(call import-module,libpng)
$(call import-module,box2d)
$(call import-module,boost)

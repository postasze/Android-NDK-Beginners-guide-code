#ifndef _PACKT_CONFIGURATION_HPP_
#define _PACKT_CONFIGURATION_HPP_

#include "Types.hpp"

#include <android_native_app_glue.h>
#include <jni.h>

typedef int32_t screen_rot;

const screen_rot ROTATION_0   = 0;
const screen_rot ROTATION_90  = 1;
const screen_rot ROTATION_180 = 2;
const screen_rot ROTATION_270 = 3;

class Configuration {
public:
    Configuration(android_app* pApplication);

    screen_rot getRotation() { return mRotation; };

private:
    void findRotation(JNIEnv* pEnv);

    android_app* mApplication;
    screen_rot mRotation;
};
#endif

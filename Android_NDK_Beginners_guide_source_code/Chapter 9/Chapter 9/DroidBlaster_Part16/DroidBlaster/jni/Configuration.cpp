#include "Configuration.hpp"
#include "Log.hpp"

#include <stdlib.h>

Configuration::Configuration(android_app* pApplication) :
    mApplication(pApplication),
    mRotation(0) {
    AConfiguration* configuration = AConfiguration_new();
    if (configuration == NULL) return;

    int32_t result;
    char i18NBuffer[] = "__";
    static const char* orientation[] = {
        "Unknown", "Portrait", "Landscape", "Square"
    };
    static const char* screenSize[] = {
        "Unknown", "Small", "Normal", "Large", "X-Large"
    };
    static const char* screenLong[] = {
        "Unknown", "No", "Yes"
    };

    // Dumps current configuration.
    AConfiguration_fromAssetManager(configuration,
        mApplication->activity->assetManager);
    result = AConfiguration_getSdkVersion(configuration);
    Log::info("SDK Version : %d", result);
    AConfiguration_getLanguage(configuration, i18NBuffer);
    Log::info("Language    : %s", i18NBuffer);
    AConfiguration_getCountry(configuration, i18NBuffer);
    Log::info("Country     : %s", i18NBuffer);
    result = AConfiguration_getOrientation(configuration);
    Log::info("Orientation : %s (%d)", orientation[result], result);
    result = AConfiguration_getDensity(configuration);
    Log::info("Density     : %d dpi", result);
    result = AConfiguration_getScreenSize(configuration);
    Log::info("Screen Size : %s (%d)", screenSize[result], result);
    result = AConfiguration_getScreenLong(configuration);
    Log::info("Long Screen : %s (%d)", screenLong[result], result);
    AConfiguration_delete(configuration);


    // Attaches current thread to the Dalvik VM.
    JavaVM* javaVM = mApplication->activity->vm;
    JavaVMAttachArgs javaVMAttachArgs;
    javaVMAttachArgs.version = JNI_VERSION_1_6;
    javaVMAttachArgs.name = "NativeThread";
    javaVMAttachArgs.group = NULL;
    JNIEnv* env;
    if (javaVM->AttachCurrentThread(&env,
                    &javaVMAttachArgs) != JNI_OK) {
        Log::error("JNI error while attaching the VM");
        return;
    }
    // Finds screen rotation and get-rid of JNI.
    findRotation(env);
    mApplication->activity->vm->DetachCurrentThread();
}

void Configuration::findRotation(JNIEnv* pEnv) {
    jobject WINDOW_SERVICE, windowManager, display;
    jclass ClassActivity, ClassContext;
    jclass ClassWindowManager, ClassDisplay;
    jmethodID MethodGetSystemService;
    jmethodID MethodGetDefaultDisplay;
    jmethodID MethodGetRotation;
    jfieldID FieldWINDOW_SERVICE;

    jobject activity = mApplication->activity->clazz;

    // Classes.
    ClassActivity = pEnv->GetObjectClass(activity);
    ClassContext = pEnv->FindClass("android/content/Context");
    ClassWindowManager = pEnv->FindClass(
        "android/view/WindowManager");
    ClassDisplay = pEnv->FindClass("android/view/Display");

    // Methods.
    MethodGetSystemService = pEnv->GetMethodID(ClassActivity,
        "getSystemService",
        "(Ljava/lang/String;)Ljava/lang/Object;");
    MethodGetDefaultDisplay = pEnv->GetMethodID(
        ClassWindowManager, "getDefaultDisplay",
        "()Landroid/view/Display;");
    MethodGetRotation = pEnv->GetMethodID(ClassDisplay,
        "getRotation", "()I");

    // Fields.
    FieldWINDOW_SERVICE = pEnv->GetStaticFieldID(
      ClassContext, "WINDOW_SERVICE", "Ljava/lang/String;");

    // Retrieves Context.WINDOW_SERVICE.
    WINDOW_SERVICE = pEnv->GetStaticObjectField(ClassContext,
        FieldWINDOW_SERVICE);
    // Runs getSystemService(WINDOW_SERVICE).
    windowManager = pEnv->CallObjectMethod(activity,
        MethodGetSystemService, WINDOW_SERVICE);
    // Runs getDefaultDisplay().getRotation().
    display = pEnv->CallObjectMethod(windowManager,
        MethodGetDefaultDisplay);
    mRotation = pEnv->CallIntMethod(display, MethodGetRotation);

    pEnv->DeleteLocalRef(ClassActivity);
    pEnv->DeleteLocalRef(ClassContext);
    pEnv->DeleteLocalRef(ClassWindowManager);
    pEnv->DeleteLocalRef(ClassDisplay);
}

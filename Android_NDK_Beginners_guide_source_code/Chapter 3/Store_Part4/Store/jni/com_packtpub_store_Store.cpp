#include "com_packtpub_store_Store.h"
#include "Store.h"

/**
 * Contains the unique store instance in a static variable created
 * when library is loaded.
 */
static Store gStore;

JNIEXPORT jint JNI_OnLoad(JavaVM* pVM, void* reserved) {
    // Store initialization.
    gStore.mLength = 0;
    return JNI_VERSION_1_6;
}

JNIEXPORT jint JNICALL Java_com_packtpub_store_Store_getCount
  (JNIEnv* pEnv, jobject pObject) {
    return gStore.mLength;
}

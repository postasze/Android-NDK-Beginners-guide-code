#include "com_packtpub_store_Store.h"

JNIEXPORT jint JNICALL Java_com_packtpub_store_Store_initialize
  (JNIEnv* pEnv, jobject pObject) {
    pEnv = 0;
    return pEnv->CallIntMethod(0, 0);
}

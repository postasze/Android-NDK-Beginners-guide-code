#include "com_packtpub_store_Store.h"
#include <cstdlib>
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

JNIEXPORT jboolean JNICALL Java_com_packtpub_store_Store_getBoolean
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Boolean)) {
        return entry->mValue.mBoolean;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setBoolean
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jboolean pBoolean) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Boolean;
        entry->mValue.mBoolean = pBoolean;
    }
}

JNIEXPORT jbyte JNICALL Java_com_packtpub_store_Store_getByte
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Byte)) {
        return entry->mValue.mByte;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setByte
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jbyte pByte) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Byte;
        entry->mValue.mByte = pByte;
    }
}

JNIEXPORT jchar JNICALL Java_com_packtpub_store_Store_getChar
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Char)) {
        return entry->mValue.mChar;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setChar
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jchar pChar) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Char;
        entry->mValue.mChar = pChar;
    }
}

JNIEXPORT jdouble JNICALL Java_com_packtpub_store_Store_getDouble
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Double)) {
        return entry->mValue.mDouble;
    } else {
        return 0.0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setDouble
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jdouble pDouble) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Double;
        entry->mValue.mDouble = pDouble;
    }
}

JNIEXPORT jfloat JNICALL Java_com_packtpub_store_Store_getFloat
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Float)) {
        return entry->mValue.mFloat;
    } else {
        return 0.0f;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setFloat
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jfloat pFloat) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Float;
        entry->mValue.mFloat = pFloat;
    }
}

JNIEXPORT jint JNICALL Java_com_packtpub_store_Store_getInteger
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Integer)) {
        return entry->mValue.mInteger;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setInteger
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jint pInteger) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Integer;
        entry->mValue.mInteger = pInteger;
    }
}

JNIEXPORT jlong JNICALL Java_com_packtpub_store_Store_getLong
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Long)) {
        return entry->mValue.mLong;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setLong
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jlong pLong) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Long;
        entry->mValue.mLong = pLong;
    }
}

JNIEXPORT jshort JNICALL Java_com_packtpub_store_Store_getShort
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Short)) {
        return entry->mValue.mShort;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setShort
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jshort pShort) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Short;
        entry->mValue.mShort = pShort;
    }
}

JNIEXPORT jstring JNICALL Java_com_packtpub_store_Store_getString
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_String)) {
        // Converts a C string into a Java String.
        return pEnv->NewStringUTF(entry->mValue.mString);
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setString
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jstring pString) {
    // Turns the Java string into a temporary C string.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_String;
        // Copy the temporary C string into its dynamically allocated
        // final location. Then releases the temporary string.
        jsize stringLength = pEnv->GetStringUTFLength(pString);
        entry->mValue.mString = new char[stringLength + 1];
        // Directly copies the Java String into our new C buffer.
        pEnv->GetStringUTFRegion(pString, 0, stringLength,
                                 entry->mValue.mString);
        // Append the null character for string termination.
        entry->mValue.mString[stringLength] = '\0';
    }
}

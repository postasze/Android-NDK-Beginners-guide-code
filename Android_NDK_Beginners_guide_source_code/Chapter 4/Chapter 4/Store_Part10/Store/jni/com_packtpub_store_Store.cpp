#include "com_packtpub_store_Store.h"
#include <cstdint>
#include <cstdlib>
#include "Store.h"

/**
 * Contains the unique store instance in a static variable created
 * when library is loaded.
 */
static Store gStore;

static jclass StringClass;
static jclass ColorClass;

static jmethodID MethodOnSuccessInt;
static jmethodID MethodOnSuccessString;
static jmethodID MethodOnSuccessColor;

JNIEXPORT jint JNI_OnLoad(JavaVM* pVM, void* reserved) {
    JNIEnv *env;
    if (pVM->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        abort();
    }

    // If returned class is null, an exception is raised by the VM.
    jclass StringClassTmp = env->FindClass("java/lang/String");
    if (StringClassTmp == NULL) abort();
    StringClass = (jclass) env->NewGlobalRef(StringClassTmp);
    env->DeleteLocalRef(StringClassTmp);

    jclass ColorClassTmp = env->FindClass("com/packtpub/store/Color");
    if (ColorClassTmp == NULL) abort();
    ColorClass = (jclass) env->NewGlobalRef(ColorClassTmp);
    env->DeleteLocalRef(ColorClassTmp);

    // Caches methods.
    jclass StoreClass = env->FindClass("com/packtpub/store/Store");
    if (StoreClass == NULL) abort();

    MethodOnSuccessInt = env->GetMethodID(StoreClass, "onSuccess",
            "(I)V");
    if (MethodOnSuccessInt == NULL) abort();

    MethodOnSuccessString = env->GetMethodID(StoreClass, "onSuccess",
            "(Ljava/lang/String;)V");
    if (MethodOnSuccessString == NULL) abort();

    MethodOnSuccessColor = env->GetMethodID(StoreClass, "onSuccess",
            "(Lcom/packtpub/store/Color;)V");
    if (MethodOnSuccessColor == NULL) abort();
    env->DeleteLocalRef(StoreClass);

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

        pEnv->CallVoidMethod(pThis, MethodOnSuccessInt,
                (jint) entry->mValue.mInteger);
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

        pEnv->CallVoidMethod(pThis, MethodOnSuccessString,
                (jstring) pEnv->NewStringUTF(entry->mValue.mString));
    }
}

JNIEXPORT jobject JNICALL Java_com_packtpub_store_Store_getColor
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_Color)) {
        return entry->mValue.mColor;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setColor
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jobject pColor) {
    // Save the Color reference in the store.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_Color;
        // The Java Color is going to be stored on the native side.
        // Need to keep a global reference to avoid a potential
        // garbage collection after method returns.
        entry->mValue.mColor = pEnv->NewGlobalRef(pColor);

        pEnv->CallVoidMethod(pThis, MethodOnSuccessColor,
                (jstring) entry->mValue.mColor);
    }
}

JNIEXPORT jbooleanArray JNICALL
Java_com_packtpub_store_Store_getBooleanArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_BooleanArray)) {
        jbooleanArray javaArray =
                pEnv->NewBooleanArray(entry->mLength);
        pEnv->SetBooleanArrayRegion(javaArray, 0, entry->mLength,
                                    entry->mValue.mBooleanArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setBooleanArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
   jbooleanArray pBooleanArray) {
    // Finds/creates an entry in the store and fills its content.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        entry->mType = StoreType_BooleanArray;
        jsize length = pEnv->GetArrayLength(pBooleanArray);
        uint8_t* array = new uint8_t[length];

        // Retrieves array content.
        jboolean* arrayTmp = pEnv->GetBooleanArrayElements(
                pBooleanArray, NULL);
        memcpy(array, arrayTmp, length * sizeof(uint8_t));
        pEnv->ReleaseBooleanArrayElements(pBooleanArray, arrayTmp, 0);

        entry->mType = StoreType_BooleanArray;
        entry->mValue.mBooleanArray = array;
        entry->mLength = length;
    }
}

JNIEXPORT jbyteArray JNICALL
Java_com_packtpub_store_Store_getByteArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_ByteArray)) {
        jbyteArray javaArray = pEnv->NewByteArray(entry->mLength);
        pEnv->SetByteArrayRegion(javaArray, 0, entry->mLength,
                                 entry->mValue.mByteArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setByteArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jbyteArray pByteArray) {
    // Creates a new store entry containing the C array.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        // Allocates a C array with the same size as the Java array.
        jsize length = pEnv->GetArrayLength(pByteArray);
        int8_t* array = new int8_t[length];
        // Copies Java array content directly in this new C array.
        pEnv->GetByteArrayRegion(pByteArray, 0, length, array);

        entry->mType = StoreType_ByteArray;
        entry->mLength = length;
        entry->mValue.mByteArray = array;
    }
}

JNIEXPORT jcharArray JNICALL Java_com_packtpub_store_Store_getCharArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_CharArray)) {
        jcharArray javaArray = pEnv->NewCharArray(entry->mLength);
        pEnv->SetCharArrayRegion(javaArray, 0, entry->mLength,
                                 entry->mValue.mCharArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setCharArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jcharArray pCharArray) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        jsize length = pEnv->GetArrayLength(pCharArray);
        uint16_t* array = new uint16_t[length];
        pEnv->GetCharArrayRegion(pCharArray, 0, length, array);

        entry->mType = StoreType_CharArray;
        entry->mLength = length;
        entry->mValue.mCharArray = array;
    }
}

JNIEXPORT jdoubleArray JNICALL
Java_com_packtpub_store_Store_getDoubleArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_DoubleArray)) {
        jdoubleArray javaArray = pEnv->NewDoubleArray(entry->mLength);
        pEnv->SetDoubleArrayRegion(javaArray, 0, entry->mLength,
                                   entry->mValue.mDoubleArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setDoubleArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
 jdoubleArray pDoubleArray) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        jsize length = pEnv->GetArrayLength(pDoubleArray);
        double* array = new double[length];
        pEnv->GetDoubleArrayRegion(pDoubleArray, 0, length, array);

        entry->mType = StoreType_DoubleArray;
        entry->mLength = length;
        entry->mValue.mDoubleArray = array;
    }
}

JNIEXPORT jfloatArray JNICALL
Java_com_packtpub_store_Store_getFloatArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_FloatArray)) {
        jfloatArray javaArray = pEnv->NewFloatArray(entry->mLength);
        pEnv->SetFloatArrayRegion(javaArray, 0, entry->mLength,
                                  entry->mValue.mFloatArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setFloatArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
   jfloatArray pFloatArray) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        jsize length = pEnv->GetArrayLength(pFloatArray);
        float* array = new float[length];
        pEnv->GetFloatArrayRegion(pFloatArray, 0, length, array);

        entry->mType = StoreType_FloatArray;
        entry->mLength = length;
        entry->mValue.mFloatArray = array;
    }
}

JNIEXPORT jintArray JNICALL
Java_com_packtpub_store_Store_getIntegerArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_IntegerArray)) {
        jintArray javaArray = pEnv->NewIntArray(entry->mLength);
        pEnv->SetIntArrayRegion(javaArray, 0, entry->mLength,
                                entry->mValue.mIntegerArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setIntegerArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
   jintArray pIntegerArray) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        jsize length = pEnv->GetArrayLength(pIntegerArray);
        int32_t* array = new int32_t[length];
        pEnv->GetIntArrayRegion(pIntegerArray, 0, length, array);

        entry->mType = StoreType_IntegerArray;
        entry->mLength = length;
        entry->mValue.mIntegerArray = array;
    }
}

JNIEXPORT jlongArray JNICALL
Java_com_packtpub_store_Store_getLongArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_LongArray)) {
        jlongArray javaArray = pEnv->NewLongArray(entry->mLength);
        pEnv->SetLongArrayRegion(javaArray, 0, entry->mLength,
                                 entry->mValue.mLongArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setLongArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey, jlongArray pLongArray) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        jsize length = pEnv->GetArrayLength(pLongArray);
        int64_t* array = new int64_t[length];
        pEnv->GetLongArrayRegion(pLongArray, 0, length, array);

        entry->mType = StoreType_LongArray;
        entry->mLength = length;
        entry->mValue.mLongArray = array;
    }
}

JNIEXPORT jshortArray JNICALL
Java_com_packtpub_store_Store_getShortArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_ShortArray)) {
        jshortArray javaArray = pEnv->NewShortArray(entry->mLength);
        pEnv->SetShortArrayRegion(javaArray, 0, entry->mLength,
                                  entry->mValue.mShortArray);
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setShortArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
   jshortArray pShortArray) {
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        jsize length = pEnv->GetArrayLength(pShortArray);
        int16_t* array = new int16_t[length];
        pEnv->GetShortArrayRegion(pShortArray, 0, length, array);

        entry->mType = StoreType_ShortArray;
        entry->mLength = length;
        entry->mValue.mShortArray = array;
    }
}

JNIEXPORT jobjectArray JNICALL
Java_com_packtpub_store_Store_getStringArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_StringArray)) {
        // An array of String in Java is in fact an array of object.
        jobjectArray javaArray = pEnv->NewObjectArray(entry->mLength,
                StringClass, NULL);

        // Creates a new Java String object for each C string stored.
        // Reference to the String can be removed right after it is
        // added to the Java array, as the latter holds a reference
        // to the String object.
        for (int32_t i = 0; i < entry->mLength; ++i) {
            jstring string = pEnv->NewStringUTF(
                    entry->mValue.mStringArray[i]);
            // Puts the new string in the array
            pEnv->SetObjectArrayElement(javaArray, i, string);
            // Do it here to avoid holding many useless local refs.
            pEnv->DeleteLocalRef(string);
        }
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setStringArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
   jobjectArray pStringArray) {
    // Creates a new entry with the new String array.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        // Allocates an array of C string.
        jsize length = pEnv->GetArrayLength(pStringArray);
        char** array = new char*[length];
        // Fills the C array with a copy of each input Java string.
        for (int32_t i = 0; i < length; ++i) {
            // Gets the current Java String from the input Java array.
            // Object arrays can be accessed element by element only.
            jstring string = (jstring)
                         pEnv->GetObjectArrayElement(pStringArray, i);

            jsize stringLength = pEnv->GetStringUTFLength(string);
            array[i] = new char[stringLength + 1];
            // Directly copies the Java String into our new C buffer.
            pEnv->GetStringUTFRegion(string,0,stringLength, array[i]);
            // Append the null character for string termination.
            array[i][stringLength] = '\0';

            // No need to keep a reference to the Java string anymore.
            pEnv->DeleteLocalRef(string);
        }

        entry->mType = StoreType_StringArray;
        entry->mLength = length;
        entry->mValue.mStringArray = array;
    }
}

JNIEXPORT jobjectArray JNICALL
Java_com_packtpub_store_Store_getColorArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey) {
    StoreEntry* entry = findEntry(pEnv, &gStore, pKey);
    if (isEntryValid(pEnv, entry, StoreType_ColorArray)) {
        // Creates a new array with objects of type Id.
        jobjectArray javaArray = pEnv->NewObjectArray(entry->mLength,
                ColorClass, NULL);

        // Fills the array with the Color objects stored on the native
        // side, which keeps a global reference to them. So no need
        // to delete or create any reference here.
        for (int32_t i = 0; i < entry->mLength; ++i) {
            pEnv->SetObjectArrayElement(javaArray, i,
                                        entry->mValue.mColorArray[i]);
        }
        return javaArray;
    } else {
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_packtpub_store_Store_setColorArray
  (JNIEnv* pEnv, jobject pThis, jstring pKey,
   jobjectArray pColorArray) {
    // Saves the Color array in the store.
    StoreEntry* entry = allocateEntry(pEnv, &gStore, pKey);
    if (entry != NULL) {
        // Allocates a C array of Color objects.
        jsize length = pEnv->GetArrayLength(pColorArray);
        jobject* array = new jobject[length];
        // Fills the C array with a copy of each input Java Color.
        for (int32_t i = 0; i < length; ++i) {
            // Gets the current Color object from the input Java array.
            // Object arrays can be accessed element by element only.
            jobject localColor = pEnv->GetObjectArrayElement(
                    pColorArray, i);
            // The Java Color is going to be stored on the native side
            // Need to keep a global reference to avoid a potential
            // garbage collection after method returns.
            array[i] = pEnv->NewGlobalRef(localColor);
            // We have a global reference to the Color, so we can now
            // get rid of the local one.
            pEnv->DeleteLocalRef(localColor);
        }

        entry->mType = StoreType_ColorArray;
        entry->mLength = length;
        entry->mValue.mColorArray = array;
    }
}

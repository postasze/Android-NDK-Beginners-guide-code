#ifndef _STORE_H_
#define _STORE_H_

#include <cstdint>
#include <pthread.h>
#include "jni.h"

/*
 * Constants.
 */
#define STORE_MAX_CAPACITY 16

/*
 * Types handled by the store.
 */
typedef enum {
    StoreType_Boolean,
    StoreType_Byte,
    StoreType_Char,
    StoreType_Double,
    StoreType_Float,
    StoreType_Integer,
    StoreType_Long,
    StoreType_Short,
    StoreType_String,
    StoreType_Color,
    StoreType_BooleanArray,
    StoreType_ByteArray,
    StoreType_CharArray,
    StoreType_DoubleArray,
    StoreType_FloatArray,
    StoreType_IntegerArray,
    StoreType_LongArray,
    StoreType_ShortArray,
    StoreType_StringArray,
    StoreType_ColorArray
} StoreType;

/**
 * Store data structures.
 */
typedef union {
    uint8_t   mBoolean;
    int8_t    mByte;
    uint16_t  mChar;
    double    mDouble;
    float     mFloat;
    int32_t   mInteger;
    int64_t   mLong;
    int16_t   mShort;
    char*     mString;
    jobject   mColor;
    uint8_t*  mBooleanArray;
    int8_t*   mByteArray;
    uint16_t* mCharArray;
    double*   mDoubleArray;
    float*    mFloatArray;
    int32_t*  mIntegerArray;
    int64_t*  mLongArray;
    int16_t*  mShortArray;
    char**    mStringArray;
    jobject*  mColorArray;
} StoreValue;

typedef struct {
    char* mKey;
    StoreType mType;
    StoreValue mValue;
    int32_t mLength; // Used only for arrays.
} StoreEntry;

typedef struct {
    StoreEntry mEntries[STORE_MAX_CAPACITY];
    int32_t mLength;
} Store;

/*
 * Store helper methods.
 */
bool isEntryValid(JNIEnv* pEnv, StoreEntry* pEntry, StoreType pType);
StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey);
StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey);
void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry);

/*
 * Methods to raise Java exceptions.
 */
void throwInvalidTypeException(JNIEnv* pEnv);
void throwNotExistingKeyException(JNIEnv* pEnv);
void throwStoreFullException(JNIEnv* pEnv);

/*
 * Watcher data structure.
 */
typedef struct {
    Store* mStore;
    JavaVM* mJavaVM;
    jobject mLock;
    pthread_t mThread;
    int32_t mRunning;
} StoreWatcher;

/**
 * Watcher methods.
 */
StoreWatcher* startWatcher(JavaVM* pJavaVM, Store* pStore,
        jobject pLock);
void stopWatcher(StoreWatcher* pWatcher);
void* runWatcher(void* pArgs);
void processEntry(StoreEntry* pEntry);
#endif

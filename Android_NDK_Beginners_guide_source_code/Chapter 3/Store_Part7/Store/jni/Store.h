#ifndef _STORE_H_
#define _STORE_H_

#include <cstdint>
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
    StoreType_Color
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
} StoreValue;

typedef struct {
    char* mKey;
    StoreType mType;
    StoreValue mValue;
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
#endif

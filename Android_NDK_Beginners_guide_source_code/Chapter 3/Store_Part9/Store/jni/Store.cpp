#include "Store.h"
#include <cstdlib>
#include <cstring>

bool isEntryValid(JNIEnv* pEnv, StoreEntry* pEntry, StoreType pType) {
    if (pEntry == NULL) {
        throwNotExistingKeyException(pEnv);
    } else if (pEntry->mType != pType) {
        throwInvalidTypeException(pEnv);
    }
    return !pEnv->ExceptionCheck();
}

StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey) {
    StoreEntry* entry = pStore->mEntries;
    StoreEntry* entryEnd = entry + pStore->mLength;

    // Compare requested key with every entry key currently stored
    // until we find a matching one.
    const char* tmpKey = pEnv->GetStringUTFChars(pKey, NULL);
    while ((entry < entryEnd) && (strcmp(entry->mKey, tmpKey) != 0)) {
        ++entry;
    }
    pEnv->ReleaseStringUTFChars(pKey, tmpKey);

    return (entry == entryEnd) ? NULL : entry;
}

StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey) {
    // If entry already exists in the store, releases its content
    // and keep its key.
    StoreEntry* entry = findEntry(pEnv, pStore, pKey);
    if (entry != NULL) {
        releaseEntryValue(pEnv, entry);
    }
    // If entry does not exist, create a new entry
    // right after the entries already stored.
    else {
        // Checks store can accept a new entry.
        if (pStore->mLength >= STORE_MAX_CAPACITY) {
            throwStoreFullException(pEnv);
            return NULL;
        }
        entry = pStore->mEntries + pStore->mLength;

        // Copies the new key into its final C string buffer.
        const char* tmpKey = pEnv->GetStringUTFChars(pKey, NULL);
        entry->mKey = new char[strlen(tmpKey) + 1];
        strcpy(entry->mKey, tmpKey);
        pEnv->ReleaseStringUTFChars(pKey, tmpKey);

        ++pStore->mLength;
    }
    return entry;
}

void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry) {
    switch (pEntry->mType) {
    case StoreType_String:
        delete pEntry->mValue.mString;
        break;
    case StoreType_Color:
        // Unreferences the object for garbage collection.
        pEnv->DeleteGlobalRef(pEntry->mValue.mColor);
        break;
    case StoreType_BooleanArray:
        delete[] pEntry->mValue.mBooleanArray;
        break;
    case StoreType_ByteArray:
        delete[] pEntry->mValue.mByteArray;
        break;
    case StoreType_CharArray:
        delete[] pEntry->mValue.mCharArray;
        break;
    case StoreType_DoubleArray:
        delete[] pEntry->mValue.mDoubleArray;
        break;
    case StoreType_FloatArray:
        delete[] pEntry->mValue.mDoubleArray;
        break;
    case StoreType_IntegerArray:
        delete[] pEntry->mValue.mIntegerArray;
        break;
    case StoreType_LongArray:
        delete[] pEntry->mValue.mLongArray;
        break;
    case StoreType_ShortArray:
        delete[] pEntry->mValue.mShortArray;
        break;
    case StoreType_StringArray:
        // Destroys every C string pointed by the String array
        // before releasing it.
        for (int32_t i = 0; i < pEntry->mLength; ++i) {
            delete pEntry->mValue.mStringArray[i];
        }
        delete[] pEntry->mValue.mStringArray;
        break;
    case StoreType_ColorArray:
        // Unreferences every Id before releasing the Id array.
        for (int32_t i = 0; i < pEntry->mLength; ++i) {
            pEnv->DeleteGlobalRef(pEntry->mValue.mColorArray[i]);
        }
        delete[] pEntry->mValue.mColorArray;
        break;
    }
}

void throwNotExistingKeyException(JNIEnv* pEnv) {
    jclass clazz = pEnv->FindClass(
            "com/packtpub/exception/NotExistingKeyException");
    if (clazz != NULL) {
        pEnv->ThrowNew(clazz, "Key does not exist.");
    }
    pEnv->DeleteLocalRef(clazz);
}

void throwInvalidTypeException(JNIEnv* pEnv) {
    jclass clazz = pEnv->FindClass(
            "com/packtpub/exception/InvalidTypeException");
    if (clazz != NULL) {
        pEnv->ThrowNew(clazz, "Type is invalid.");
    }
    pEnv->DeleteLocalRef(clazz);
}

void throwStoreFullException(JNIEnv* pEnv) {
    jclass clazz = pEnv->FindClass(
            "com/packtpub/exception/StoreFullException");
    if (clazz != NULL) {
        pEnv->ThrowNew(clazz, "Store is full.");
    }
    pEnv->DeleteLocalRef(clazz);
}

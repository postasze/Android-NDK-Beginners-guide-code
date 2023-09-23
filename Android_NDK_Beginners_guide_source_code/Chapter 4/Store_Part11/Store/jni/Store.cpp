#include "Store.h"
#include <cstdlib>
#include <cstring>
#include <unistd.h>

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

StoreWatcher* startWatcher(JavaVM* pJavaVM, Store* pStore,
        jobject pLock) {
    StoreWatcher* watcher = new StoreWatcher();
    watcher->mJavaVM = pJavaVM;
    watcher->mStore = pStore;
    watcher->mLock = pLock;
    watcher->mRunning = true;

    // Initializes and launches the native thread.
    pthread_attr_t lAttributes;
    if (pthread_attr_init(&lAttributes)) abort();
    if (pthread_create(&watcher->mThread, &lAttributes,
                            runWatcher, watcher)) abort();
    return watcher;
}

void stopWatcher(StoreWatcher* pWatcher) {
    pWatcher->mRunning = false;
}

void* runWatcher(void* pArgs) {
    StoreWatcher* watcher = (StoreWatcher*) pArgs;
    Store* store = watcher->mStore;

    JavaVM* javaVM = watcher->mJavaVM;
    JavaVMAttachArgs javaVMAttachArgs;
    javaVMAttachArgs.version = JNI_VERSION_1_6;
    javaVMAttachArgs.name = "NativeThread";
    javaVMAttachArgs.group = NULL;

    // Attaches current thread to the Dalvik VM so that it is known
    // from Java and can call Java code.
    JNIEnv* env;
    if (javaVM->AttachCurrentThreadAsDaemon(&env,
            &javaVMAttachArgs) != JNI_OK) abort();
    // Runs the thread loop.
    while (true) {
        sleep(5); // In seconds.

        // Critical section beginning, one thread at a time.
        // Entries cannot be added or modified.
        env->MonitorEnter(watcher->mLock);
        if (!watcher->mRunning) break;

        StoreEntry* entry = watcher->mStore->mEntries;
        StoreEntry* entryEnd = entry + watcher->mStore->mLength;
        while (entry < entryEnd) {
            processEntry(entry);
            ++entry;
        }

        // Critical section end.
        env->MonitorExit(watcher->mLock);
    }

    // Stops the thread. It is very important to always detach an
    // attached thread. Allowed if thread is already detached.
    javaVM->DetachCurrentThread();
    delete watcher;
    pthread_exit(NULL);
}


void processEntry(StoreEntry* pEntry) {
    switch (pEntry->mType) {
    case StoreType_Integer:
        if (pEntry->mValue.mInteger > 100000) {
            pEntry->mValue.mInteger = 100000;
        } else if (pEntry->mValue.mInteger < -100000) {
            pEntry->mValue.mInteger = -100000;
        }
        break;
    }
}

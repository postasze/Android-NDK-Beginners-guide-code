#ifndef _STORE_H_
#define _STORE_H_

#include <cstdint>

/*
 * Constants.
 */
#define STORE_MAX_CAPACITY 16

/*
 * Types handled by the store.
 */
typedef enum {
} StoreType;

/**
 * Store data structures.
 */
typedef union {
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
#endif

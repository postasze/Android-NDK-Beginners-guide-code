#ifndef _PACKT_RESOURCE_HPP_
#define _PACKT_RESOURCE_HPP_

#include "Types.hpp"

#include <android_native_app_glue.h>

struct ResourceDescriptor {
    int32_t mDescriptor;
    off_t mStart;
    off_t mLength;
};

class Resource {
public:
    Resource(android_app* pApplication, const char* pPath);

    const char* getPath() { return mPath; };

    status open();
    void close();
    status read(void* pBuffer, size_t pCount);

    ResourceDescriptor descriptor();

    bool operator==(const Resource& pOther);

private:
    Resource(const Resource&);
    void operator=(const Resource&);

    const char* mPath;
    AAssetManager* mAssetManager;
    AAsset* mAsset;
};

#endif

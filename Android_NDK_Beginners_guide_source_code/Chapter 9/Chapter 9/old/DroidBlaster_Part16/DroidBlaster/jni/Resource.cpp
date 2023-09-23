#include "Resource.hpp"

#include <sys/stat.h>

Resource::Resource(android_app* pApplication, const char* pPath):
    mPath(std::string("/sdcard/") + pPath),
//    mAssetManager(pApplication->activity->assetManager),
//    mAsset(NULL)
    mInputStream()/*, mBuffer(NULL)*/ {
}

status Resource::open() {
//    mAsset = AAssetManager_open(mAssetManager, mPath,
//                                AASSET_MODE_UNKNOWN);
//    return (mAsset != NULL) ? STATUS_OK : STATUS_KO;
    mInputStream.open(mPath.c_str(), std::ios::in | std::ios::binary);
    return mInputStream ? STATUS_OK : STATUS_KO;
}

void Resource::close() {
//    if (mAsset != NULL) {
//        AAsset_close(mAsset);
//        mAsset = NULL;
//    }
    mInputStream.close();
//    delete[] mBuffer; mBuffer = NULL;
}

status Resource::read(void* pBuffer, size_t pCount) {
//    int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
//    return (lReadCount == pCount) ? STATUS_OK : STATUS_KO;
    mInputStream.read((char*)pBuffer, pCount);
    return (!mInputStream.fail()) ? STATUS_OK : STATUS_KO;
}

off_t Resource::getLength() {
//    return AAsset_getLength(mAsset);
    struct stat filestatus;
    if (stat(mPath.c_str(), &filestatus) >= 0) {
        return filestatus.st_size;
    } else {
        return -1;
    }
}

//ResourceDescriptor Resource::descriptor() {
//    ResourceDescriptor lDescriptor = { -1, 0, 0 };
//    AAsset* lAsset = AAssetManager_open(mAssetManager, mPath,
//                                        AASSET_MODE_UNKNOWN);
//    if (lAsset != NULL) {
//        lDescriptor.mDescriptor = AAsset_openFileDescriptor(
//            lAsset, &lDescriptor.mStart, &lDescriptor.mLength);
//        AAsset_close(lAsset);
//    }
//    return lDescriptor;
//}

bool Resource::operator==(const Resource& pOther) {
    return mPath == pOther.mPath;
}

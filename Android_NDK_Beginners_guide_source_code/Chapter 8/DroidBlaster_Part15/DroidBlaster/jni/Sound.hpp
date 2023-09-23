#ifndef _PACKT_SOUND_HPP_
#define _PACKT_SOUND_HPP_

class SoundManager;

#include "Resource.hpp"
#include "Types.hpp"

class Sound {
public:
    Sound(android_app* pApplication, Resource* pResource);

    const char* getPath();
    uint8_t* getBuffer() { return mBuffer; };
    off_t getLength() { return mLength; };

    status load();
    status unload();

private:
    Sound(const Sound&);
    void operator=(const Sound&);
    friend class SoundManager;

    Resource* mResource;
    uint8_t* mBuffer; off_t mLength;
};
#endif

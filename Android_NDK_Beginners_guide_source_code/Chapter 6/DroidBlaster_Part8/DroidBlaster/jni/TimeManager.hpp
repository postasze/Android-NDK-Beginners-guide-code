#ifndef _PACKT_TIMEMANAGER_HPP_
#define _PACKT_TIMEMANAGER_HPP_

#include "Types.hpp"

class TimeManager {
public:
    TimeManager();

    void reset();
    void update();

    double now();
    float elapsed() { return mElapsed; };
    float elapsedTotal() { return mElapsedTotal; };

private:
    TimeManager(const TimeManager&);
    void operator=(const TimeManager&);

    double mFirstTime;
    double mLastTime;
    float mElapsed;
    float mElapsedTotal;
};
#endif

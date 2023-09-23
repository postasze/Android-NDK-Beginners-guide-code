#include "Log.hpp"
#include "TimeManager.hpp"

#include <unistd.h>

#define BOOST_TEST_MODULE droidblaster_test_module
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(suiteTimeManager)

BOOST_AUTO_TEST_CASE(testTimeManagerTest_elapsed)
{
    TimeManager timeManager;
    timeManager.reset();

    sleep(1);
    timeManager.update();
    BOOST_REQUIRE(timeManager.elapsed() > 0.9f);
    BOOST_REQUIRE(timeManager.elapsed() < 1.2f);

    sleep(1);
    timeManager.update();
    BOOST_REQUIRE(timeManager.elapsed() > 0.9f);
    BOOST_REQUIRE(timeManager.elapsed() < 1.2f);
}

BOOST_AUTO_TEST_SUITE_END()

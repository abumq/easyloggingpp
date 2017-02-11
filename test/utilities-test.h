
#ifndef UTILITIES_TEST_H_
#define UTILITIES_TEST_H_

#include "test.h"

#include <thread>
#include <chrono>

TEST(UtilitiesTest, SafeDelete) {
    int* i = new int(12);
    ASSERT_TRUE(i != nullptr);
    safeDelete(i);
    ASSERT_EQ(nullptr, i);
}

TEST(UtilitiesTest, PerformanceTrackerTest) {
    {
        TIMED_SCOPE(timer, "5 seconds wait");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    {
        TIMED_SCOPE(timer, "1200 milliseconds wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    }
    {
        TIMED_SCOPE(timer, "20 milliseconds wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

#endif // UTILITIES_TEST_H_

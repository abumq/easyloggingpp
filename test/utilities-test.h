
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
    {
        TIMED_SCOPE(timer, "20 microseconds wait");
        std::this_thread::sleep_for(std::chrono::microseconds(20));
    }
    {
        TIMED_SCOPE(timer, "886 milliseconds wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(886));
    }
    {
        TIMED_SCOPE(timer, "1500 milliseconds wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    {
        TIMED_SCOPE(timer, "1400 milliseconds wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(1400));
    }
    {
        TIMED_SCOPE(timer, "1600 milliseconds wait");
        std::this_thread::sleep_for(std::chrono::milliseconds(1600));
    }
}

#endif // UTILITIES_TEST_H_


#ifndef HITCOUNTER_TESTS_H_
#define HITCOUNTER_TESTS_H_

#include "test-helpers.h"

TEST(RegisteredHitCountersTest, Validation) {
    RegisteredHitCounters r;

    // Ensure no hit counters are registered yet
    EXPECT_TRUE(r.empty());

    unsigned long int line = __LINE__;
    r.validate(__FILE__, line, 2);

    // Confirm size
    EXPECT_EQ(2, r.size());

    // Confirm hit count
    EXPECT_EQ(1, r.getCounter(__FILE__, line)->hitCounts());

    // Confirm validations
    EXPECT_TRUE(r.validate(__FILE__, line, 2));
    EXPECT_FALSE(r.validate(__FILE__, line, 2));

    EXPECT_TRUE(r.validate(__FILE__, line, 2));
    EXPECT_FALSE(r.validate(__FILE__, line, 2));

    EXPECT_TRUE(r.validate(__FILE__, line, 2));
    EXPECT_FALSE(r.validate(__FILE__, line, 2));

    line = __LINE__;
    r.validate(__FILE__, line, 3);
    // Confirm size
    EXPECT_EQ(2, r.size());
    // Confirm hitcounts
    EXPECT_EQ(1, r.getCounter(__FILE__, line)->hitCounts());

    // Confirm validations
    EXPECT_FALSE(r.validate(__FILE__, line, 3));
    EXPECT_TRUE(r.validate(__FILE__, line, 3));
    EXPECT_FALSE(r.validate(__FILE__, line, 3));

    EXPECT_FALSE(r.validate(__FILE__, line, 3));
    EXPECT_TRUE(r.validate(__FILE__, line, 3));
    EXPECT_FALSE(r.validate(__FILE__, line, 3));

    EXPECT_FALSE(r.validate(__FILE__, line, 3));
    EXPECT_TRUE(r.validate(__FILE__, line, 3));
    EXPECT_FALSE(r.validate(__FILE__, line, 3));

    EXPECT_FALSE(r.validate(__FILE__, line, 3));
    EXPECT_TRUE(r.validate(__FILE__, line, 3));
    EXPECT_FALSE(r.validate(__FILE__, line, 3));

    EXPECT_FALSE(r.validate(__FILE__, line, 3));
    EXPECT_TRUE(r.validate(__FILE__, line, 3));
    EXPECT_FALSE(r.validate(__FILE__, line, 3));

    // Confirm size once again
    EXPECT_EQ(2, r.size());
}

#endif /* HITCOUNTER_TESTS_H_ */

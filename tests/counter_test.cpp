#include <gtest/gtest.h>
#include "counter.h"
#include <thread>
#include <vector>
#include <climits>

// ?? forward declaration (ÂÀÆËÈÂÎ)
void __counter_set_value_for_tests(Counter*, int);

TEST(CounterTest, Basic) {
    Counter* c = counter_create();
    int v;

    EXPECT_EQ(counter_increment(c, &v), COUNTER_OK);
    EXPECT_EQ(v, 1);

    EXPECT_EQ(counter_decrement(c, &v), COUNTER_OK);
    EXPECT_EQ(v, 0);

    EXPECT_EQ(counter_get(c, &v), COUNTER_OK);
    EXPECT_EQ(v, 0);

    EXPECT_EQ(counter_reset(c), COUNTER_OK);
    EXPECT_EQ(counter_get(c, &v), COUNTER_OK);
    EXPECT_EQ(v, 0);

    counter_destroy(c);
}

TEST(CounterTest, Concurrent) {
    Counter* c = counter_create();

    const int N = 8;
    const int K = 10000;

    std::vector<std::thread> threads;

    for (int i = 0; i < N; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < K; ++j)
                counter_increment(c, nullptr);
            });
    }

    for (auto& t : threads) t.join();

    int v;
    counter_get(c, &v);

    EXPECT_EQ(v, N * K);

    counter_destroy(c);
}

TEST(CounterTest, Overflow) {
    Counter* c = counter_create();
    int v;

    __counter_set_value_for_tests(c, INT_MAX);

    EXPECT_EQ(counter_increment(c, &v), COUNTER_ERR_OVERFLOW);

    counter_destroy(c);
}

TEST(CounterTest, Underflow) {
    Counter* c = counter_create();
    int v;

    __counter_set_value_for_tests(c, INT_MIN);

    EXPECT_EQ(counter_decrement(c, &v), COUNTER_ERR_UNDERFLOW);

    counter_destroy(c);
}

TEST(CounterTest, Null) {
    int v;

    EXPECT_EQ(counter_increment(nullptr, &v), COUNTER_ERR_NULL);
    EXPECT_EQ(counter_get(nullptr, &v), COUNTER_ERR_NULL);
    EXPECT_EQ(counter_get(nullptr, nullptr), COUNTER_ERR_NULL);
}

TEST(CounterTest, Lifecycle) {
    Counter* c = counter_create();
    counter_destroy(c);
    counter_destroy(nullptr);
}
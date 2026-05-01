#include "counter.h"
#include <atomic>
#include <climits>
#include <new>   // 🔥 ОБОВ'ЯЗКОВО

struct Counter {
    std::atomic<int> value;
};

Counter* counter_create(void) {
    Counter* c = new (std::nothrow) Counter;
    if (!c) return nullptr;
    c->value.store(0);
    return c;
}

void counter_destroy(Counter* c) {
    delete c;
}

CounterStatus counter_increment(Counter* c, int* out_value) {
    if (!c) return COUNTER_ERR_NULL;

    int current = c->value.load();

    while (true) {
        if (current == INT_MAX)
            return COUNTER_ERR_OVERFLOW;

        if (c->value.compare_exchange_weak(current, current + 1)) {
            if (out_value) *out_value = current + 1;
            return COUNTER_OK;
        }
    }
}

CounterStatus counter_decrement(Counter* c, int* out_value) {
    if (!c) return COUNTER_ERR_NULL;

    int current = c->value.load();

    while (true) {
        if (current == INT_MIN)
            return COUNTER_ERR_UNDERFLOW;

        if (c->value.compare_exchange_weak(current, current - 1)) {
            if (out_value) *out_value = current - 1;
            return COUNTER_OK;
        }
    }
}

CounterStatus counter_get(const Counter* c, int* out_value) {
    if (!c || !out_value) return COUNTER_ERR_NULL;

    *out_value = c->value.load();
    return COUNTER_OK;
}

CounterStatus counter_reset(Counter* c) {
    if (!c) return COUNTER_ERR_NULL;

    c->value.store(0);
    return COUNTER_OK;
}

#ifdef BUILD_TESTS
void __counter_set_value_for_tests(Counter* c, int value) {
    if (!c) return;
    c->value.store(value);
}
#endif
#ifndef COUNTER_H
#define COUNTER_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Counter Counter;

    typedef enum {
        COUNTER_OK = 0,
        COUNTER_ERR_NULL = 1,
        COUNTER_ERR_OVERFLOW = 2,
        COUNTER_ERR_UNDERFLOW = 3
    } CounterStatus;

    Counter* counter_create(void);
    void counter_destroy(Counter* c);

    CounterStatus counter_increment(Counter* c, int* out_value);
    CounterStatus counter_decrement(Counter* c, int* out_value);
    CounterStatus counter_get(const Counter* c, int* out_value);
    CounterStatus counter_reset(Counter* c);

    /* 🔥 helper для тестів */
    void counter_set_value(Counter* c, int value);

#ifdef __cplusplus
}
#endif
#endif
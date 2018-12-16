#include "stdio.h"

/* -----------------------------------------------------------------------------
    BASE
----------------------------------------------------------------------------- */

typedef struct{
    void* state;
    void (*get_answer)(void* state);
} base_t;

void base_get_answer(base_t* b) {
    b->get_answer(b->state);
}

/* -----------------------------------------------------------------------------
    DERIVED ONE
----------------------------------------------------------------------------- */

typedef struct{
    int answer;
} foo_t;

void foo_get_answer(void* state) {
    printf("foo's answer is %i\n", ((foo_t*)state)->answer);
}

base_t foo_construct(foo_t* foo) {
    base_t base = {foo, &foo_get_answer};
    return base;
};

/* -----------------------------------------------------------------------------
    DERIVED TWO
----------------------------------------------------------------------------- */

typedef struct{
    char const* answer;
} bar_t;

void bar_get_answer(void* state) {
    printf("bar's answer is \'%s\'\n", ((bar_t*)state)->answer);
}

base_t bar_construct(bar_t* bar) {
    base_t base = {bar, &bar_get_answer};
    return base;
};

/* -----------------------------------------------------------------------------
    USAGE
----------------------------------------------------------------------------- */

int main(void) {
    foo_t foo_state = {42};
    base_t base_with_foo = foo_construct(&foo_state);

    base_get_answer(&base_with_foo);

    bar_t bar_state = {"nothing is real"};
    base_t base_with_bar = bar_construct(&bar_state);

    base_get_answer(&base_with_bar);
}

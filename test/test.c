#include "unity.h"
#include "num.h"
#include "new.h"
#include "integration.h"

struct param_t {
    num_t alpha;
} ;

num_t fn1 (num_t x, void* params)
{
    struct param_t* p = (struct param_t *) params;
    return num_mul(p->alpha, num_mul(x, x));
}

void
setUp (void)
{
    // set stuff up here
}

void
tearDown (void)
{
    // clean stuff up here
}

void
test_simple_integral (void)
{
    const num_t from = new(num, 0.0, 0.0);
    const num_t   to = new(num, 1.0, 0.0);
    const num_t    n = new(num, 100.0, 0.0);
    struct param_t p = { .alpha = new(num, 3.0, 0.0) };

    func_t f;
    f.fn = &fn1;
    f.params = &p;
    
    const double ret = num_to_double(integrate(&f, from, to));
    delete(from); delete(to); delete(n);
        
    TEST_ASSERT_EQUAL_DOUBLE( 1.0, ret );    
}

int
main (void)
{
    UNITY_BEGIN();
            
    RUN_TEST(test_simple_integral);
    
    return UNITY_END();
}

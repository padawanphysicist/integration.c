#include "unity.h"
#include "num.h"
#include "new.h"
#include "integration.h"

void
fn1 (num_t res, const num_t x, const void* ctx)
{
    const double alpha = *(const double *)ctx;
    num_pow_d(res, x, 2.0);
    num_mul_d(res, res, alpha);
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
    num_t from, to, res;

    from = new(num), to = new(num), res = new(num);

    num_zero(res);
    num_zero(from);
    num_set_d(to, 1.0);
    
    num_t n;
    n = new(num);
    num_set_d(n, 100.0);
    
    //struct param_t p = { .alpha = new(num, 3.0, 0.0) };
    const double alpha = 3.0;

    /* func_t f; */
    /* f.fn = &fn1; */
    /* f.params = &alpha; */
    
    integrate(res, &fn1, &alpha, from, to);
    delete(from); delete(to); delete(n), delete(res);
        
    TEST_ASSERT_EQUAL_DOUBLE( 1.0, num_to_d(res) );
}

int
main (void)
{
    UNITY_BEGIN();
            
    RUN_TEST(test_simple_integral);
    
    return UNITY_END();
}

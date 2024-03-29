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

void f (num_t res, const num_t x, const void *ctx)
{
    (void)ctx;
    //return exp(-x / 5.) * (2. + sin(2. * x));
    num_t fac1, fac2;
    fac1 = new(num), fac2 = new(num);

    /* fac1 = exp(-x / 5.) */
    num_mul_d(fac1, x, -1.0/5.0); /* fac1 = -x / 5.0 */
    num_exp(fac1, fac1); /* fac1 = exp(fac1) */

    /* fac2 = (2. + sin(2. * x)) */
    num_mul_d(fac2, x, 2.0);
    num_sin(fac2, fac2);
    num_add_d(fac2, fac2, 2.0);

    num_mul(res, fac1, fac2);

    delete(fac1), delete(fac2);
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
    
    integrate(res, &fn1, &alpha, from, to, -1 /*qsimp*/);
    delete(from); delete(to); delete(n), delete(res);
        
    TEST_ASSERT_EQUAL_DOUBLE( 1.0, num_to_d(res) );
}

void test_tanhsinh (void)
{
        static const double exact = 9.10823960732299650652;

        num_t from, to, tolerance, result, est_err, num_eval;
	from = new(num), to = new(num), tolerance = new(num);
	result = new(num), est_err = new(num), num_eval = new(num);

    /* Test 1 */
	num_set_d(from, 0.0), num_set_d(to, 10.0);
	num_set_d(tolerance, 1.0e-6);

    /* tanhsinh_quad(result, f, NULL, from, to, tolerance, est_err, num_eval); */
    integrate(result, &f, NULL, from, to, 0 /*tanh-sinh*/);
    printf("integral[0, 10] exp(-x/5) (2 + sin(2 x)):\n"
           "  exact:    %.17g\n"
           "  numeric:  %.17g +/- %.2g (%u evaluations)\n",
           exact, num_to_d(result), num_to_d(est_err), (int)num_to_d(num_eval));
    //check(exact, num_to_d(result), num_to_d(tolerance));
    TEST_ASSERT_EQUAL_DOUBLE( exact, num_to_d(result) );

    delete(from), delete(to), delete(tolerance), delete(result), delete(est_err), delete(num_eval);


    
    //}
    //{
    //    static const double power = 5.;
    //    static const double exact = 0.417685255920550038197;
    //    result = tanhsinh_quad(g, &power, 0, 1, tolerance, NULL, NULL);
    //    printf("integral[0,  1] (1 - x)^5 x^(-1/3):\n"
    //           "  exact:    %.17g\n"
    //           "  numeric:  %.17g\n",
    //           exact, result);
    //    check(exact, result, tolerance);
    //}
    //return 0;
}

int
main (void)
{
    UNITY_BEGIN();
            
    RUN_TEST(test_simple_integral);
    RUN_TEST(test_tanhsinh);
    
    return UNITY_END();
}

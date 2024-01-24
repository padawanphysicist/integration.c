#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "new.h"
#include "integrate.h"

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

//double g(double x, const void *ctx)
//{
//    const double power = *(const double *)ctx;
//    return pow(1. - x, power) * pow(x, -1. / 3.);
//}

void check(double exact, double result, double tolerance) {
    if (!(fabs(exact - result) < tolerance)) {
        fprintf(stderr, "error: result does not seem to match\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    //static const double tolerance = 1e-6;
    //double est_err, result;
    //unsigned num_eval;
	    //{
        static const double exact = 9.10823960732299650652;

        num_t from, to, tolerance, result, est_err, num_eval;
	from = new(num), to = new(num), tolerance = new(num);
	result = new(num), est_err = new(num), num_eval = new(num);

    /* Test 1 */
	num_set_d(from, 0.0), num_set_d(to, 10.0);
	num_set_d(tolerance, 1.0e-6);

    tanhsinh_quad(result, f, NULL, from, to, tolerance, est_err, num_eval);

    printf("integral[0, 10] exp(-x/5) (2 + sin(2 x)):\n"
           "  exact:    %.17g\n"
           "  numeric:  %.17g +/- %.2g (%u evaluations)\n",
           exact, num_to_d(result), num_to_d(est_err), (int)num_to_d(num_eval));
    check(exact, num_to_d(result), num_to_d(tolerance));

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
    return 0;
}

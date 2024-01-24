#ifndef __INTEGRATE_H__
#define __INTEGRATE_H__
/** @file
    Numerical integration in one dimension using the tanh-sinh quadrature.

    This quadrature method provides good results for a variety of functions
    and is about as general purpose as feasible.  It is also fairly robust at
    handling singularities at the endpoints of the integral.

    The method is described in the [paper by Masatake Mori and Masaaki
    Sugihara][1] and is sometimes referred to as the double-exponential method.

    The code was originally written by [John D. Cook][2], who has dedicated
    the code to the [public domain][3].

    [1]: http://dx.doi.org/10.1016/S0377-0427%2800%2900501-X
    [2]: http://codeproject.com/Articles/31550/Fast-Numerical-Integration
    [3]: https://creativecommons.org/publicdomain/zero/1.0
*/

#include "num.h"

void
tanhsinh_quad(num_t res,
		void (*f)(num_t res, const num_t x, const void *ctx), 
		const void *ctx,
		const num_t a, const num_t b, 
		const num_t abs_err,
		num_t est_err, 
		num_t num_eval);
#endif

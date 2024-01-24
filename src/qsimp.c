#include<stdlib.h>
#include<stdio.h>
#include "new.h"
#include "num.h"

void
integration_qsimp (num_t res,
          void (*f)(num_t res, const num_t x, const void *ctx),
          const void *ctx,
          num_t min,
          num_t max,
          num_t gp)
//double integr8or( double (*f)(double), double min, double max, int gp )
{
    /* double range = max - min; */
    num_t range, del;

    range = new(num), del = new(num);
    num_sub(range, max, min);

	/* double del = range / gp; */
    num_div(del, range, gp);
    
	/* double integral = 0; */
    num_zero(res);

    num_t low, high, mid;
    low = new(num), high = new(num), mid = new(num);
    num_t A,B,C;
    A = new(num), B = new(num), C = new(num);
    num_t fac1, fac2;
    fac1 = new(num), fac2 = new(num);
	for( int i = 0; i < (int)num_to_d(gp); i++ )
	{
		/* double low = min + del*i; */
        num_mul_d(low, del, (double)i);
        num_add(low, min, low);
		/* double high = min + del*(i+1); */
        num_mul_d(high, del, (double)i+1);
        num_add(high, min, high);
		/* double mid = (low+high)/2; */
        num_add(mid, low, high);
        num_mul_d(mid, mid, 0.5);

		/* double A = (*f)(low); */
        (*f)(A, low, ctx);
		/* double B = (*f)(mid); */
        (*f)(B, mid, ctx);
		/* double C = (*f)(high); */
        (*f)(C, high, ctx);

		/* integral += (high-low)/6.0 * (A + 4.0*B + C); */
        num_mul_d(fac1, B, 4.0);
        num_add(fac1, fac1, A);
        num_add(fac1, fac1, C);
        num_sub(fac2, high, low);
        num_mul_d(fac2, fac2, 1.0/6.0);
        num_mul(fac1, fac1, fac2);
        num_add(res, res, fac1);
	}
    delete(fac1), delete(fac2);
    delete(low), delete(high), delete(mid);
    delete(A), delete(B), delete(C);

	//num_set(res, integral);

    delete(range), delete(del);
}

/*
 * This file is part of integration.c (https://github.com/padawanphysicist/integration.c).
 *
 * integration.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * integration.c is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * integration.c. If not, see <https://www.gnu.org/licenses/>.
 */

/** 
 * @file integration.c
 * @brief Implementation of the main routines.
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "integration.h"
#include "new.h"
#include "log.h"

static num_t
int_simpson (const num_t from, const num_t to, const num_t n, func_t* fun);

num_t
integrate (func_t* fun, const num_t from, const num_t to)
{
    return int_simpson(from, to, new(num, 100.0, 0.0), fun);
}

#ifndef EVAL_FN
#define EVAL_FN(foo,x) ((foo->fn)(x, (foo->params)))
#endif
static num_t
int_simpson (const num_t from, const num_t to, const num_t n, func_t* fun)
{
    num_t h = num_div(num_sub(to, from), n);
    num_t sum1 = new(num, 0.0, 0.0);
    num_t sum2 = new(num, 0.0, 0.0);
    const int N = (int) num_to_double(n);
   
    for (int i = 0; i < N; i++)
    {
        num_t arg = num_add(from,
                      num_add(num_mul(h, new(num, (double) i, 0.0)),
                              num_div(h, new(num, 2.0, 0.0))));
        sum1 = num_add(sum1, EVAL_FN(fun, arg));
        delete(arg);
    }

    for (int i = 1; i < N; i++)
    {
        num_t arg = num_add(from,
                      num_mul(h, new(num, (double) i, 0.0)));
        sum2 = num_add(sum2, EVAL_FN(fun, arg));
        delete(arg);
    }

    num_t ret = num_mul(
        num_div(h, new(num, 6.0, 0.0)),
        num_add(EVAL_FN(fun, from),
                num_add(EVAL_FN(fun, to),
                        num_add(
                            num_mul(sum1, new(num, 4.0, 0.0)),
                            num_mul(sum2, new(num, 2.0, 0.0))))));
    delete(h); delete(sum1); delete(sum2);

    return ret;
}
#ifdef EVAL_FN
#undef EVAL_FN
#endif

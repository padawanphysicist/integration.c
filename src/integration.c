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
#include "qsimp.h"
#include "qtanhsinh.h"
#include "new.h"
#include "num.h"
#include "log.h"

void
integrate (num_t res,
           void (*f)(num_t res, const num_t x, const void *ctx), 
           const void *ctx,
           const num_t from,
           const num_t to,
           const int method)
{
    switch (method) {
    case 0:
        // tanh-sinh quadrature
        num_t tolerance, est_err, num_eval;
        tolerance = new(num), est_err = new(num), num_eval = new(num);
        num_set_d(tolerance, 1.0e-15);
        tanhsinh_quad(res, f, ctx, from, to, tolerance, est_err, num_eval);
        delete(tolerance), delete(est_err), delete(num_eval);
        break;
    default:
        num_t n;
        n = new(num);
        num_set_d(n, 100.0);
        integration_qsimp(res, f, ctx, from, to, n);
        delete(n);
    }
}

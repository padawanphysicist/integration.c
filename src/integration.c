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
#include "new.h"
#include "num.h"
#include "log.h"

void
integrate (num_t res,
           void (*f)(num_t res, const num_t x, const void *ctx), 
           const void *ctx,
           const num_t from,
           const num_t to)
{
    const int method = -1;

    switch (method) {
    case 0:
        // code block
        break;
    default:
        num_t n;
        n = new(num);
        num_set_d(n, 100.0);
        integration_qsimp(res, f, ctx, from, to, n);
        delete(n);
    }
}

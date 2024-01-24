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
 * @file integration.h
 * @brief Interface for the main routine.
 */
#ifndef __INTEGRATION_H_
#define __INTEGRATION_H_

#include "num.h"
#include "new.h"

typedef struct
{
    num_t (*fn)();
    void* params;
} func_t;

void
integrate (num_t res,
           void (*f)(num_t res, const num_t x, const void *ctx), 
           const void *ctx,
           const num_t from,
           const num_t to);

#endif /* __INTEGRATION_H_ */

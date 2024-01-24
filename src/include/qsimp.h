#include "num.h"

void
integration_qsimp (num_t res,
          void (*f)(num_t res, const num_t x, const void *ctx),
          const void *ctx,
          num_t min,
          num_t max,
                   num_t gp);

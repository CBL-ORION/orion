#ifndef NUMERIC_FUNC_H
#define NUMERIC_FUNC_H 1

#include <stdint.h>

#include "util/util.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
float64 factorial_int64_t(uint8_t n);
float64 polyeval_horners_float64(const float64* coefficients, size_t polynomial_degree, float64 x );
float64 matlab_polyeval_horners_float64(const float64* coefficients, size_t polynomial_degree, float64 x );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NUMERIC_FUNC_H */

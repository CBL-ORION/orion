#ifndef NUMERIC_FUNC_H
#define NUMERIC_FUNC_H 1

#include <stdint.h>

#include "util/util.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern float64 factorial_int64_t(uint8_t n);
extern float64 polyeval_horners_float64(const float64* coefficients, size_t polynomial_degree, float64 x );
extern float64 matlab_polyeval_horners_float64(const float64* coefficients, size_t polynomial_degree, float64 x );

extern float64* matlab_colonop_float64(float64 min, float64 delta, float64 max, size_t* length);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NUMERIC_FUNC_H */

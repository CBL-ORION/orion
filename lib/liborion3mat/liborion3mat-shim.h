#ifndef LIBORION3MAT_SHIM_H
#define LIBORION3MAT_SHIM_H 1

/* The following typedef is needed for clang since it does not define char16_t
 * in C99 mode. Using uint16_t will be equivalent.
 */
#include <stdint.h>
typedef uint16_t char16_t;


#include "liborion3mat.h"

#endif /* LIBORION3MAT_SHIM_H */

#ifndef UTIL_LIKELY_H
#define UTIL_LIKELY_H 1

#include "config/config.h"

/* likely - macros for annotating likely/unlikely branches in the code
 *
 * See <https://github.com/rustyrussell/ccan/blob/master/ccan/likely/_info> for
 * more information
 */

#if HAVE_BUILTIN_EXPECT

#define likely(cond) __builtin_expect(!!(cond), 1)
#define unlikely(cond) __builtin_expect(!!(cond), 0)

#else /* ! HAVE_BUILTIN_EXPECT */

#define likely(cond) (!!(cond))
#define unlikely(cond) (!!(cond))

#endif /* HAVE_BUILTIN_EXPECT */

#endif /* UTIL_LIKELY_H */

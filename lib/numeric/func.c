#include <stdint.h>
#include <math.h>

#include "numeric/func.h"
#include "util/util.h"

#define ORION_FACTORIAL_PRECALC \
	{ \
		/*  0! */ 1.0F, \
		/*  1! */ 1.0F, \
		/*  2! */ 2.0F, \
		/*  3! */ 6.0F, \
		/*  4! */ 24.0F, \
		/*  5! */ 120.0F, \
		/*  6! */ 720.0F, \
		/*  7! */ 5040.0F, \
		/*  8! */ 40320.0F, \
		/*  9! */ 362880.0F, \
		/* 10! */ 3628800.0F, \
		/* 11! */ 39916800.0F, \
		/* 12! */ 479001600.0F, \
		/* 13! */ 6227020800.0F, \
		/* 14! */ 87178291200.0F, \
		/* 15! */ 1307674368000.0F, \
		/* 16! */ 20922789888000.0F, \
		/* 17! */ 355687428096000.0F, \
		/* 18! */ 6402373705728000.0F, \
		/* 19! */ 121645100408832000.0F, \
		/* 20! */ 2432902008176640000.0F, \
		/* 21! */ 51090942171709440000.0F, \
		/* 22! */ 1124000727777607680000.0F, \
		/* 23! */ 25852016738884976640000.0F, \
		/* 24! */ 620448401733239439360000.0F, \
		/* 25! */ 15511210043330985984000000.0F, \
		/* 26! */ 403291461126605635584000000.0F, \
		/* 27! */ 10888869450418352160768000000.0F, \
		/* 28! */ 304888344611713860501504000000.0F, \
		/* 29! */ 8841761993739701954543616000000.0F, \
		/* 30! */ 265252859812191058636308480000000.0F, \
		/* 31! */ 8222838654177922817725562880000000.0F, \
		/* 32! */ 263130836933693530167218012160000000.0F, \
		/* 33! */ 8683317618811886495518194401280000000.0F, \
		/* 34! */ 295232799039604140847618609643520000000.0F \
	}

float64 factorial_int64_t(int8_t n) {
	/* TODO note that this use of static variables is not re-entrant (not
	 * thread-safe)
	 */

	/* maximum for a float64 such that
	 *     fact(MAX_FACTORIAL_N_FLOAT64) <= FLT_MAX
	 * and
	 *     isinf( fact(MAX_FACTORIAL_N_FLOAT64 + 1 ) ) == 1 # positive infinity
	 * */
	const int MAX_FACTORIAL_N_FLOAT64 = 170;
	/* this table is static because it is stored for all function calls */
	static double* factorial_lut = NULL;
	static int factorial_lut_max = 0;
	/* precalculated factorial values */
	static int64_t factorial_lut_precalc[] = ORION_FACTORIAL_PRECALC;
	if( !factorial_lut ) {
		NEW_COUNT(factorial_lut, double, MAX_FACTORIAL_N_FLOAT64 + 1);
		/*
		 * Subtract one because we start at 0.
		 *
		 * So if the LUT has 2 elements, then the maximum value of n
		 * that has been precalculated is 1.
		 */
		factorial_lut_max = sizeof(factorial_lut_precalc)/sizeof(double) - 1;
		for( int i = 0; i <= factorial_lut_max; i++) {
			factorial_lut[i] = factorial_lut_precalc[i];
		}
	}

	if( n > MAX_FACTORIAL_N_FLOAT64 ) {
		die("factorial of %d can not be represented using float. Maximum is %d", n, MAX_FACTORIAL_N_FLOAT64);
	}

	if( n > factorial_lut_max ) {
		for( int cur_n = factorial_lut_max + 1; cur_n <= n; cur_n++ ) {
			factorial_lut[ cur_n ] = cur_n * factorial_lut[ cur_n - 1 ];
		}
		factorial_lut_max = n;
	}

	return factorial_lut[n];
}

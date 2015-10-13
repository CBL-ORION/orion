#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "numeric/func.h"

int main(void) {
	plan(1 * 5);

	{/* 1 tests */
		size_t n;
		float64* vec = matlab_colonop_float64(0, 1, 3, &n);;
		is_int( 4, n, "0:1:3 is of length 4");
		free(vec);
	}
	{/* 1 tests */
		size_t n;
		float64* vec = matlab_colonop_float64(0, 1.1, 3, &n);;
		is_int( 3, n, "0:1.1:3 is of length 3");
		free(vec);
	}
	{/* 1 tests */
		size_t n;
		float64* vec = matlab_colonop_float64(0, 1, 3.1, &n);;
		is_int( 4, n, "0:1.1:3 is of length 4");
		free(vec);
	}
	{/* 1 tests */
		size_t n;
		float64* vec = matlab_colonop_float64(0, 1, 3.9, &n);;
		is_int( 4, n, "0:1.1:3 is of length 4");
		free(vec);
	}
	{/* 1 tests */
		size_t n;
		float64* vec = matlab_colonop_float64(0, 1, 4, &n);;
		is_int( 5, n, "0:1.1:3 is of length 5");
		free(vec);
	}
}

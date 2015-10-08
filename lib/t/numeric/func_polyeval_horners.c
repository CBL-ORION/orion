#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "numeric/func.h"

int main(void) {
	plan(3 * 2);

	{/* 3 tests */
		float64 poly[] = { 4, 2, 3 };
		diag( "f(x) = %.2f + %.2fx + %.2fx^2", poly[0], poly[1], poly[2] );
		is_double(  4, polyeval_horners_float64(poly, 2, 0), 0,
				"f(0) = c_0 = 4");
		is_double(  9, polyeval_horners_float64(poly, 2, 1), 0,
				"f(1) = 4+2+3 = 9");
		is_double( 20, polyeval_horners_float64(poly, 2, 2), 0,
				"f(2) = 4+4+12 = 20");
	}

	{/* 3 tests */
		/*
		% MATLAB
		poly = [ 4 2 3 ];
		polyval( poly, [0 1 2] )
		% ans = 3    9   23
		*/
		float64 poly[] = { 4, 2, 3 };
		diag( "f(x) = %.2fx^2 + %.2fx + %.2f", poly[0], poly[1], poly[2] );
		is_double(  3, matlab_polyeval_horners_float64(poly, 2, 0), 0,
				"f(0) = c_0 = 3");
		is_double(  9, matlab_polyeval_horners_float64(poly, 2, 1), 0,
				"f(1) = 4+2+3 = 9");
		is_double( 23, matlab_polyeval_horners_float64(poly, 2, 2), 0,
				"f(2) = 4+4+12 = 23");
	}

}

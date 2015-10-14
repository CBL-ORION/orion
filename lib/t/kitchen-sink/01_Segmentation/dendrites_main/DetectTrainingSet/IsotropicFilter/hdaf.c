#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/hdaf.h"

#include <stdio.h>
/*
factor = 0.25;
SZ = 5;
[xx,yy,zz] = ndgrid(0:SZ-2, 0:SZ-1, 0:SZ);
x = sqrt( (factor*xx).^2 + (factor*yy).^2 + (factor*zz).^2 );
x_hdaf = hdaf(3, 5, x)

*/

/* size of the array */
#define SZ 5
int main(void) {
	const size_t ctr = (SZ-1)/2;
	const float64 eps = 1e-9;
	const float64 factor = 0.25;

	ndarray3* x = ndarray3_new(SZ-1, SZ, SZ+1);

	plan(1 + 1*(x->sz[0]*x->sz[1]));

	NDARRAY3_LOOP_OVER_START(x, i,j,k) {
		pixel_type v = sqrt(
			SQUARED(factor*i)
			+ SQUARED(factor*j)
			+ SQUARED(factor*k));
		ndarray3_set(x, i,j,k,   v );
	} NDARRAY3_LOOP_OVER_END;
	/*[>DEBUG<]ndarray3_printf_matlab( x, "x", "%-3.4f" );*/
	ndarray3* x_hdaf = orion_hdaf(3.0, 5.0, x);
	/*[>DEBUG<]ndarray3_printf_matlab( x_hdaf, "x_hdaf", "%-8.2e" );*/

/* 1 test */
	ok( NULL != x_hdaf, "hdaf() is calculated");

/* SQUARED(SZ) tests */
	/* data obtained via MATLAB version of code */
	float64 x_hdaf_expect_in_slice_2[SZ-1][SZ] = {
		{  0.001554557843011070L,  0.000483684919144825L,  2.30331534344049e-05L, 3.57020210992147e-07L,  2.94795099944829e-09L },
		{  0.000483684919144825L,  0.000164238527645446L,  9.31038842869133e-06L, 1.69570022484907e-07L,  1.58626005230393e-09L },
		{  2.30331534344049e-05L,  9.31038842869133e-06L,  7.70805732461795e-07L, 2.06591265844898e-08L,  2.66383757976786e-10L },
		{  3.57020210992147e-07L,  1.69570022484907e-07L,  2.06591265844898e-08L,  8.6474221809541e-10L,  1.67944333599867e-11L }
	};
	/*[>DEBUG<]ndarray3_printf_matlab(x_hdaf, STRINGIZE(x_hdaf), "%3.2e");*/

	for( int i = 0; i < x_hdaf->sz[0]; i++ ) {
		for( int j = 0; j < x_hdaf->sz[1]; j++ ) {
			is_double(
				x_hdaf_expect_in_slice_2[i][j],
				ndarray3_get( x_hdaf, i,j,2 ),
				eps, "value at [%d,%d,2] is as expected", i,j);
		}
	}

	ndarray3_free( x_hdaf );
	ndarray3_free( x );

	return EXIT_SUCCESS;
}

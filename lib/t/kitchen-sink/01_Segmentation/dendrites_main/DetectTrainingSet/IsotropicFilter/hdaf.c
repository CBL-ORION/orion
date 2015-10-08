#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/hdaf.h"

#include <stdio.h>
/*
[xx,yy,zz] = ndgrid(0:4, 0:4, 0:4);
x = sqrt( (xx - 2).^2 + (yy - 2).^2 + (zz - 2).^2 );
x_hdaf = hdaf(3, 5, x)

*/

/* size of the array */
#define SZ 5
int main(void) {
	const size_t ctr = (SZ-1)/2;
	const float64 eps = 1e-15;

	plan(1 + 1*SQUARED(SZ));

	ndarray3* x = ndarray3_new(SZ, SZ, SZ);
	NDARRAY3_LOOP_OVER_START(x, i,j,k) {
		pixel_type v = sqrt(
			SQUARED(i-ctr)
			+ SQUARED(j-ctr)
			+ SQUARED(k-ctr));
		ndarray3_set(x, i,j,k,   v );
	} NDARRAY3_LOOP_OVER_END;
	/*[>DEBUG<]ndarray3_printf( x, "x", "%-3.2e" );*/
	ndarray3* x_hdaf = orion_hdaf(3.0, 5.0, x);
	/*[>DEBUG<]ndarray3_printf( x_hdaf, "x_hdaf", "%-8.2e" );*/

/* 1 test */
	ok( NULL != x_hdaf, "hdaf() is calculated");

/* SQUARED(SZ) tests */
	/* data obtained via MATLAB version of code */
	float64 x_hdaf_expect_in_slice_2[SZ][SZ] = {
		{  1.2011536328547e-26L,   1.62118205557411e-20L,    4.26915920514493e-18L,  1.62118205557411e-20L,   1.2011536328547e-26L },
		{ 1.62118205557411e-20L,   3.54754049593545e-12L,    4.08675894799675e-08L,  3.54754049593545e-12L,  1.62118205557411e-20L },
		{ 4.26915920514493e-18L,   4.08675894799675e-08L,                       1L,  4.08675894799675e-08L,  4.26915920514493e-18L },
		{ 1.62118205557411e-20L,   3.54754049593545e-12L,    4.08675894799675e-08L,  3.54754049593545e-12L,  1.62118205557411e-20L },
		{  1.2011536328547e-26L,   1.62118205557411e-20L,    4.26915920514493e-18L,  1.62118205557411e-20L,   1.2011536328547e-26L }
	};

	for( int j = 0; j < SZ; j++ ) {
		for( int k = 0; k < SZ; k++ ) {
			is_double(
				x_hdaf_expect_in_slice_2[j][k],
				ndarray3_get( x_hdaf, 2,j,k ),
				eps, "value at [2,%d,%d] is as expected", j,k);
		}
	}


	return EXIT_SUCCESS;
}

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

int main(void) {
	plan(1);

	/* TODO */
	const size_t sz = 5;
	const size_t ctr = (sz-1)/2;
	ndarray3* x = ndarray3_new(sz, sz, sz);
	NDARRAY3_LOOP_OVER_START(x, i,j,k) {
		pixel_type v = sqrt(
			SQUARED(i-ctr)
			+ SQUARED(j-ctr)
			+ SQUARED(k-ctr));
		ndarray3_set(x, i,j,k,   v );
	} NDARRAY3_LOOP_OVER_END;
	/*[>DEBUG<]ndarray3_printf( x, "x", "%-3.2e" );*/
	ndarray3* x_hdaf = orion_hdaf(3.0, 5.0, x);
	/*DEBUG*/ndarray3_printf( x_hdaf, "x_hdaf", "%-8.2e" );

	return EXIT_SUCCESS;
}

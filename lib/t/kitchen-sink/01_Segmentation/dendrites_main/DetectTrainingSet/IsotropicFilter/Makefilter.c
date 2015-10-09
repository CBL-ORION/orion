#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/Makefilter.h"

/*
% MATLAB
sz = 5;
n = 3.0;
s = 5.0;
mk = Makefilter(sz, sz, sz, n, s, 1 )

*/

/* size of the array */
#define SZ 5
int main(void) {
	const size_t ctr = (SZ-1)/2;
	const float64 eps = 1e-15;

	plan(1);

	ndarray3* mk = orion_Makefilter( SZ, SZ, SZ, 3.0, 5.0, orion_Makefilter_FLAG_A );
	ndarray3_printf( mk , "mk", "%3.2e");

	return EXIT_SUCCESS;
}

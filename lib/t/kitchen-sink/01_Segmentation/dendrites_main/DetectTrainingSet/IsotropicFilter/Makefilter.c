#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/Makefilter.h"

/*
% MATLAB
sz = 5;
mk = Makefilter(sz-1, sz, sz+1, 3, 5.0, 1 )

*/

int main(void) {
	const float64 eps = 1e-15;

	plan(3);

	const int hdaf_approx_degree = 3;
	const float scale_factor = 5.0;

	{
		/* even-sized filter */
		const size_t SZ = 6;
		ndarray3* mk = orion_Makefilter( SZ, SZ, SZ, hdaf_approx_degree, scale_factor, orion_Makefilter_FLAG_A );
		/*[>DEBUG<]ndarray3_printf_matlab( mk , "mk-even", "%8.4e");*/
		ok( ndarray3_is_isotropic( mk, eps ), "Makefilter() output is isotropic for an even-sized filter" );
		ndarray3_free(mk);
	}

	{
		/* odd-sized filter */
		const size_t SZ = 5;
		ndarray3* mk = orion_Makefilter( SZ, SZ, SZ, hdaf_approx_degree, scale_factor, orion_Makefilter_FLAG_A );
		/*[>DEBUG<]ndarray3_printf_matlab( mk , "mk-odd", "%8.4e");*/
		ok( ndarray3_is_isotropic( mk, eps ), "Makefilter() output is isotropic for an odd-sized filter" );
		ndarray3_free(mk);
	}

	{
		/* asymmetric-sized filter */
		const size_t SZ = 5;
		ndarray3* mk = orion_Makefilter( SZ-1, SZ, SZ+1, hdaf_approx_degree, scale_factor, orion_Makefilter_FLAG_A );
		/*[>DEBUG<]ndarray3_printf_matlab( mk , "mk-asym", "%8.4e");*/
		ok( ndarray3_is_isotropic( mk, eps ), "Makefilter() output is isotropic for an asymmetric-sized filter" );
		ndarray3_free(mk);
	}

	return EXIT_SUCCESS;
}

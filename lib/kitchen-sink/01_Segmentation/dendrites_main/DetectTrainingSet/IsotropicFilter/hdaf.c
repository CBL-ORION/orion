/*
 * Refactor: hdaf
 */
#include "hdaf.h"

#include <math.h>

#include "numeric/func.h"

/*
 * orion_hdaf( hdaf_approx_degree, scaling_constant, x)
 *
 * hdaf_approx_degree : number of coeffecients used for the Taylor polynomial expansion
 *
 * scaling_constant : used to scale each of the values of x by pow(scaling_constant, 2)
 *
 * x : input points to calculate the HDAF result
 *
 */
ndarray3* orion_hdaf(
		const int hdaf_approx_degree,
		const float scaling_constant,
		ndarray3* x) {
	ndarray3* x_scale = ndarray3_new_with_size_from_ndarray3( x );
	ndarray3* out = ndarray3_new_with_size_from_ndarray3( x );

	NDARRAY3_LOOP_OVER_START(x, i, j, k) {
		/* x_scale = x * c_nk ^2 */
		ndarray3_set(x_scale, i,j,k,
			ndarray3_get(x, i,j,k) * pow(scaling_constant, 2)
			);
	} NDARRAY3_LOOP_OVER_END;

	/* computing coefficients for Taylor expansion of
	 * exponential to degree `hdaf_approx_degree` */
	const size_t coeff_sz = hdaf_approx_degree + 1;
	float64* coeff;
	NEW_COUNT( coeff, float64, coeff_sz );
	for( int coeff_idx = 0; coeff_idx < coeff_sz; ++coeff_idx ) {
		/* `n` ranges from `hdaf_approx_degree` to 0 */
		int n = hdaf_approx_degree - coeff_idx;
		coeff[ coeff_idx ] = 1 / factorial_int64_t( n );
	}
	/*[>DEBUG<]for( int i = 0 ; i < coeff_sz; i++ ) { printf("coeff[%d] = %f\n", i, coeff[i]); }*/

	NDARRAY3_LOOP_OVER_START(out, i, j, k) {
		pixel_type x_scale_ijk = ndarray3_get( x_scale, i,j,k);
		float64 out_ijk;

		/* evaluate the Taylor expansion of
		 * exponential to degree `hdaf_approx_degree` */
		out_ijk = matlab_polyeval_horners_float64(coeff, hdaf_approx_degree, x_scale_ijk );

		/* evaluate the filter */
		out_ijk *= exp( -x_scale_ijk );

		/* save it in the ndarray3 `out` */
		ndarray3_set(out, i,j,k, out_ijk);
	} NDARRAY3_LOOP_OVER_END;

	free(coeff);
	ndarray3_free(x_scale);

	return out;
}

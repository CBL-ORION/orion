/* TODO
 *
 * Refactor: Makefilter
 */

typedef enum {
	orion_Makefilter_FLAG_A,
	orion_Makefilter_FLAG_B,
	orion_Makefilter_FLAG_C
} orion_Makefilter_flag;

#include "ndarray/ndarray3.h"
#include "segmentation/def.h"
#include "numeric/def.h"
#include "util/util.h"

ndarray3* orion_Makefilter(
		size_t nx, size_t ny, size_t nz,
		int hdaf_approx_degree,
		float scale_factor,
		orion_Makefilter_flag flag) {
	size_t n[] = { nx, ny, nz };
	const size_t ndims = sizeof( n ) / sizeof( size_t ); /* 3 dimensions */

	float kmin[ndims];
	float kmax[ndims];
	float dk[ndims];
	size_t k_axis_sz[ndims];
	float* k_axis[ndims];

	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		kmin[dim_idx] = 0;
		kmax[dim_idx] = M_PI;

		dk[dim_idx] = 2*M_PI / n[dim_idx];

		/* MATLAB's colonop:
		 *
		 * see <https://www.mathworks.com/matlabcentral/answers/143255-how-does-the-colon-operator-work>
		 */
		k_axis_sz[dim_idx] = (size_t) floor(
				  (kmax[dim_idx] - kmin[dim_idx])
				/ dk[dim_idx] );
		NEW_COUNT(k_axis[dim_idx], float, k_axis_sz[dim_idx]);

		for(size_t k_axis_idx = 0; k_axis_idx < k_axis_sz[dim_idx]; k_axis_idx++) {
			/* Do not use direct summation to avoid numerical
			 * errors (i.e., do not use
			 *     `running_value += * dk[dim_idx]`
			 * )
			 *
			 * NOTE: it might be better to use Kahan summation
			 * algorithm
			 */
			k_axis[dim_idx][k_axis_idx] =
				kmin[dim_idx]
				+ k_axis_idx * dk[dim_idx];
		}
	}

	ndarray3* Kxyz = ndarray3_new(
			k_axis_sz[0],
			k_axis_sz[1],
			k_axis_sz[2] );
	for( size_t ka_idx_0 = 0; ka_idx_0 < k_axis_sz[0]; ka_idx_0++ ) {
	for( size_t ka_idx_1 = 0; ka_idx_1 < k_axis_sz[1]; ka_idx_1++ ) {
	for( size_t ka_idx_2 = 0; ka_idx_2 < k_axis_sz[2]; ka_idx_2++ ) {
		/* kx .^ 2 + ky .^ 2 + kz .^ 2 */
		ndarray3_set(Kxyz, ka_idx_0, ka_idx_1, ka_idx_2,
				  SQUARED(k_axis[0][ka_idx_0])
				+ SQUARED(k_axis[1][ka_idx_1])
				+ SQUARED(k_axis[2][ka_idx_2]) );
	}}}

	float kd = scale_factor * kmax[0];
	float sigma = sqrt( 2.0 * hdaf_approx_degree + 1 ) / kd;


	float nh[ndims];
	bool flip[ndims];
	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		nh[dim_idx] = floor( n[dim_idx] / 2.0 ) + 1;
		flip[dim_idx] = !!( n[dim_idx] % 2  );
	}
}

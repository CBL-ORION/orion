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

	ndarray3* K[3];
	ndarray3* Kxyz = ndarray3_new(
			k_axis_sz[0],
			k_axis_sz[1],
			k_axis_sz[2] );
	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		K[dim_idx] = ndarray3_new_with_size_from_ndarray3( Kxyz );
	}

	NDARRAY3_LOOP_OVER_START( Kxyz, i0, i1, i2) {
		ndarray3_set( K[0], i0, i1, i2, k_axis_sz[i0] );
		ndarray3_set( K[1], i0, i1, i2, k_axis_sz[i1] );
		ndarray3_set( K[1], i0, i1, i2, k_axis_sz[i2] );

		/* kx .^ 2 + ky .^ 2 + kz .^ 2 */
		ndarray3_set(Kxyz, i0, i1, i2,
				  SQUARED(k_axis[0][i0])
				+ SQUARED(k_axis[1][i1])
				+ SQUARED(k_axis[2][i2]) );
	} NDARRAY3_LOOP_OVER_END;

	float kd = scale_factor * kmax[0];
	float sigma = sqrt( 2.0 * hdaf_approx_degree + 1 ) / kd;

	float nh[ndims];
	bool flip[ndims];
	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		nh[dim_idx] = floor( n[dim_idx] / 2.0 ) + 1;
		flip[dim_idx] = !!( n[dim_idx] % 2  );
	}

	ndarray3* filt = ndarray3_new( n[0], n[1], n[2] );
	NDARRAY3_LOOP_OVER_START( filt, i0, i1, i2) {
		/* set all values to 0 */
		ndarray3_set( filt, i0, i1, i2, 0 );
	} NDARRAY3_LOOP_OVER_END;

	if( flag == orion_Makefilter_FLAG_A ) {
		/* TODO */
	} else if( flag == orion_Makefilter_FLAG_B ) {
		/* TODO */
	} else if( flag == orion_Makefilter_FLAG_C ) {
		/* TODO */
	}
}

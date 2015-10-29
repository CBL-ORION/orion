/*
 * Refactor: Makefilter
 */

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/Makefilter.h"

#include "segmentation/def.h"
#include "numeric/func.h"
#include "numeric/def.h"
#include "util/util.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/hdaf.h"

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
	float64* k_axis[ndims];

	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		kmin[dim_idx] = 0;
		kmax[dim_idx] = M_PI;

		dk[dim_idx] = 2*M_PI / n[dim_idx];

		/* kmin(:) : dk(:) : kmax(:) */
		k_axis[dim_idx] =
			matlab_colonop_float64(kmin[dim_idx], dk[dim_idx], kmax[dim_idx], &k_axis_sz[dim_idx]);
	}

	ndarray3* Kxyz = ndarray3_new(
			k_axis_sz[0],
			k_axis_sz[1],
			k_axis_sz[2] );

	NDARRAY3_LOOP_OVER_START( Kxyz, i0, i1, i2) {
		/* kx .^ 2 + ky .^ 2 + kz .^ 2 */
		ndarray3_set(Kxyz, i0, i1, i2,
				  SQUARED(k_axis[0][i0])
				+ SQUARED(k_axis[1][i1])
				+ SQUARED(k_axis[2][i2]) );
	} NDARRAY3_LOOP_OVER_END;

	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		free(k_axis[dim_idx]);
	}

	float kd = scale_factor * kmax[0];
	float sigma = sqrt( 2.0 * hdaf_approx_degree + 1 ) / (sqrt(2) * kd);

	float nh[ndims];
	bool flip[ndims];
	for( int dim_idx = 0; dim_idx < ndims; dim_idx++ ) {
		flip[dim_idx] =    ( n[dim_idx] % 2   );
		nh[dim_idx] = floor( n[dim_idx] / 2.0 ) + flip[dim_idx];
		/*[>DEBUG<]printf("nh[%d] = %f ; flip[%d] = %d\n", dim_idx, nh[dim_idx], dim_idx, flip[dim_idx]);*/
	}

	ndarray3* filt = ndarray3_new( n[0], n[1], n[2] );
	NDARRAY3_LOOP_OVER_START( filt, i0, i1, i2) {
		/* set all values to 0 */
		ndarray3_set( filt, i0, i1, i2, 0 );
	} NDARRAY3_LOOP_OVER_END;

	if( flag == orion_Makefilter_FLAG_A ) {
		/* TODO */
		ndarray3* half_filt = orion_hdaf(hdaf_approx_degree, sigma, Kxyz);
		/* Generating Laplacian filter */
		/*[>DEBUG<]ndarray3_printf_matlab(half_filt, STRINGIZE(half_filt), "%10.8g");*/
		/*[>DEBUG<]ndarray3_printf_matlab(Kxyz, STRINGIZE(Kxyz), "%10.8f");*/


		/* make the rest of the filter symmetric across the centre */
		for( int i = 0; i < nh[0]; i++ ) {
			for( int j = 0; j < nh[1]; j++ ) {
				for( int k = 0; k < nh[2]; k++ ) {
					/* - Kxyz * half_filt */
					pixel_type v = - ndarray3_get( Kxyz, i,j,k )
						* ndarray3_get(half_filt, i,j,k);

					ndarray3_set(filt, i, j, k,   v);

					/* indices reflected across the axes */
					ptrdiff_t fi = filt->sz[0]-i-1;
					ptrdiff_t fj = filt->sz[1]-j-1;
					ptrdiff_t fk = filt->sz[2]-k-1;

					/* flip once */
					ndarray3_set(filt, fi, j, k,   v);
					ndarray3_set(filt,  i,fj, k,   v);
					ndarray3_set(filt,  i, j,fk,   v);

					/* flip twice */
					ndarray3_set(filt, fi,fj, k,   v);
					ndarray3_set(filt, fi, j,fk,   v);
					ndarray3_set(filt,  i,fj,fk,   v);

					/* flip thrice */
					ndarray3_set(filt, fi,fj,fk,   v);
				}
			}
		}

		ndarray3_free(half_filt);
		ndarray3_free(Kxyz);

		return filt;
	} else if( flag == orion_Makefilter_FLAG_B ) {
		TODO(Implement high-pass filter --- dead code)
		/* NOTE: zaki: this is dead code in the original MATLAB implementation */
		die("Unimplemented flag: %s\n", STRINGIZE(orion_Makefilter_FLAG_B));
	} else if( flag == orion_Makefilter_FLAG_C ) {
		TODO(Implement low-pass filter --- dead code)
		/* NOTE: zaki: this is dead code in the original MATLAB implementation */
		die("Unimplemented flag: %s\n", STRINGIZE(orion_Makefilter_FLAG_C));
	}
}

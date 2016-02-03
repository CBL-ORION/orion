#include <stdlib.h>
#include <tap/basic.h>

#include <math.h>
#include "ndarray/ndarray3.h"
#include "numeric/def.h"

ndarray3* gen_radial(ndarray3* n) {
	NDARRAY3_LOOP_OVER_START( n, i, j, k) {
		ndarray3_set( n, i,j,k,  sqrt(
				  SQUARED( i - (n->sz[0]-1)/2.0 )
				+ SQUARED( j - (n->sz[1]-1)/2.0 )
				+ SQUARED( k - (n->sz[2]-1)/2.0 )
				) );
	} NDARRAY3_LOOP_OVER_END;

	return n;
}

int main(void) {
	plan(2 + 10);

	/* epsilon is small because we can be more exact for this data */
	const pixel_type eps = 1e-20;

	{/* 2 tests */
		ndarray3* nd_radial = ndarray3_new(3, 4, 5);
		gen_radial( nd_radial );

		/*[>DEBUG<]ndarray3_printf( nd_radial, "nd_radial", "%.5f" );*/

		ok( ndarray3_is_isotropic(nd_radial, eps), "radial array is isotropic" );

		ndarray3_set( nd_radial, 1, 1, 1, -M_PI); /* change single value */
		ok( !ndarray3_is_isotropic(nd_radial, eps),
				"changing a single value of the radial array makes it no longer isotropic" );

		ndarray3_free( nd_radial );
	}


	{/* 10 tests */
		ndarray3* nd_trivial = ndarray3_new(3, 4, 5);

		/* flat field */
		NDARRAY3_LOOP_OVER_START( nd_trivial, i, j, k) {
			ndarray3_set( nd_trivial, i,j,k,  1.0 );
		} NDARRAY3_LOOP_OVER_END;

		ok( ndarray3_is_isotropic(nd_trivial, 1e-20),
			"a flat field is isotropic" );

		/* change single value on corner */
		ndarray3_set( nd_trivial, 0, 0, 0, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps),
			"flat field no longer isotropic after changing single corner" );

		/* change all corners */
		/* define last index in each dim */
		size_t a = nd_trivial->sz[0]-1,
		       b = nd_trivial->sz[1]-1,
		       c = nd_trivial->sz[2]-1;
		ndarray3_set( nd_trivial, 0, 0, 0, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 1: still not isotropic" );
		ndarray3_set( nd_trivial, a, 0, 0, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 2: still not isotropic" );
		ndarray3_set( nd_trivial, 0, b, 0, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 3: still not isotropic" );
		ndarray3_set( nd_trivial, 0, 0, c, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 4: still not isotropic" );
		ndarray3_set( nd_trivial, a, b, 0, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 5: still not isotropic" );
		ndarray3_set( nd_trivial, a, 0, c, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 6: still not isotropic" );
		ndarray3_set( nd_trivial, 0, b, c, -M_PI);
		ok( ! ndarray3_is_isotropic(nd_trivial, eps), "corner 7: still not isotropic" );

		/* final corner */
		ndarray3_set( nd_trivial, a, b, c, -M_PI);
		ok( ndarray3_is_isotropic(nd_trivial, eps),   "corner 8: after setting last corner, flat field is isotropic" );

		/*[>DEBUG<]ndarray3_printf( nd_trivial, "nd_trivial", "%.5f" );*/

		ndarray3_free( nd_trivial );
	}

	return EXIT_SUCCESS;
}

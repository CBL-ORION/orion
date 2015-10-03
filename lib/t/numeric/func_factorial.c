#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <float.h>

#include "numeric/func.h"

#include <stdio.h>

int main(void) {
	plan(10);

	/* test factorial function */
	is_double( 1, factorial_int64_t(0), 0, "0!");
	is_double( 1, factorial_int64_t(1), 0, "1!");
	is_double( 2, factorial_int64_t(2), 0, "2!");
	is_double( 87178291200.0L, factorial_int64_t(14), 0, "14!");

	is_double( 6402373705728000.0L, factorial_int64_t(18), 0, "18!");

	is_double( 2432902008176640000.0L, factorial_int64_t(20), 0, "20!");

	is_double(295232799039604140847618609643520000000.0L, factorial_int64_t(34), 0, "34!");

	is_double(815915283247897734345611269596115894272000000000.0L, factorial_int64_t(40), 0, "40!" );

	is_double(815915283247897734345611269596115894272000000000.0L, factorial_int64_t(40), 0, "40!" );

	is_double(7257415615307998967396728211129263114716991681296451376543577798900561843401706157852350749242617459511490991237838520776666022565442753025328900773207510902400430280058295603966612599658257104398558294257568966313439612262571094946806711205568880457193340212661452800000000000000000000000000000000000000000.0L,
			factorial_int64_t(170), 0, "170!" );

	/*[>DEBUG<]for( int i = 0; i <= 40; i++ ) {
		printf("%d! = %.0f\n", i, factorial_int64_t(i) );
	}*/

	return EXIT_SUCCESS;
}

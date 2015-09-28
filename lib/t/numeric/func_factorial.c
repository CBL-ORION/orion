#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <float.h>

#include "numeric/func.h"

int main(void) {
	plan(3 + 1);

	/* TODO test factorial function */
	is_double( 1, factorial_float(0), 0, "0!");
	is_double( 1, factorial_float(1), 0, "1!");
	is_double( 2, factorial_float(2), 0, "2!");
	is_double( 87178291200.0F, factorial_float(14), 0, "14!");

	is_double( 6402373705728000.0F, factorial_float(18), 0, "18!");

	is_double( 2432902008176640000.0F, factorial_float(20), 0, "20!");

	float max_float32_fact = factorial_float(34);
	ok(FLT_MAX > max_float32_fact, 0, "FLT_MAX > 34!", "maxi");
	is_double(295232799039604140847618609643520000000.0F , max_float32_fact, 1e32, "34!");

	for( int i = 0; i <= 34; i++ ) {
		printf("%d! = %lf\n", i, factorial_float(i) );
	}

	return EXIT_SUCCESS;
}

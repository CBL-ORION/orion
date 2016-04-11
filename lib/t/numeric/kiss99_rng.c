#include <tap/basic.h>
#include <stdint.h>

#include "numeric/kiss99_rng.h"

/* This is a test main program. It should compile and print 7 0's. */
int main(int argc, char** argv) {
	int i; uint32_t k;

	kiss99_rng_state* state = kiss99_rng_state_new();
	kiss99_rng_set_table(state, 12345,65435,34221,12345,9983651,95746118);

	plan(7);

	for(i=1;i<1000001;i++){k=kiss99_rng_LFIB4(state);} is_int(0, k-1064612766U, "LFIB4");
	for(i=1;i<1000001;i++){k=kiss99_rng_SWB(state) ;} is_int(0, k- 627749721U, "SWB");
	for(i=1;i<1000001;i++){k=kiss99_rng_KISS(state) ;} is_int(0, k-1372460312U, "KISS");
	for(i=1;i<1000001;i++){k=kiss99_rng_CONG(state) ;} is_int(0, k-1529210297U, "CONG");
	for(i=1;i<1000001;i++){k=kiss99_rng_SHR3(state) ;} is_int(0, k-2642725982U, "SHR3");
	for(i=1;i<1000001;i++){k=kiss99_rng_MWC(state) ;} is_int(0, k- 904977562U, "MWC");
	for(i=1;i<1000001;i++){k=kiss99_rng_FIB(state) ;} is_int(0, k-3519793928U, "FIB");

	return EXIT_SUCCESS;
}

#include "liborion3mat/liborion3mat-shim.h"

int main() {
	/* Initialize the MATLAB Compiler Runtime global state */
	if (!mclInitializeApplication(NULL,0)) {
		fprintf(stderr,  "Could not initialize the MATLAB runtime properly.\n" );
		exit(EXIT_FAILURE);
	}
	if( !liborion3matInitialize() ) {
		fprintf(stderr,  "Could not initialize liborion3mat properly.\n" );
		exit(EXIT_FAILURE);
	}
	char* path_to_input = "test-data/DIADEM/NPF/Input_NPF023_D.txt";
	mxArray* path_to_input_mx = mxCreateString( path_to_input ); /* allocate */
	mlfORION3(path_to_input_mx);
	mxDestroyArray(path_to_input_mx); /* free */
	return 0;
}

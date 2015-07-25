#include <stdlib.h>
#include <stdio.h>

#include "simple-log/simplelog.h"

int main( int argc, char * argv[] ) {
	LOG_INFO("Starting %s", argv[0] );



	LOG_INFO("Stopping %s", argv[0] );
	return EXIT_SUCCESS;
}

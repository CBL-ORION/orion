#include <stdlib.h>
#include <stdio.h>

#include "simple-log/simplelog.h"

#include "container/array.h"

/*
  if( strcmp( argv[i], "--scale" ) == 0 ) {
	array_insert_float( scales, atof( argv[i + 1] ) );
  } else if( strcmp( argv[i], "--input" ) == 0 ) {
	WARN_UNIMPLEMENTED
  } else if(  strcmp( argv[i], "--output" ) == 0 ) {
	WARN_UNIMPLEMENTED
  }
*/

int main( int argc, char * argv[] ) {
	LOG_INFO("Starting %s", argv[0] );

	/*
		--scale 1.0
		--scale 2.0
		--scale 3.0
		--input  filename.mhd
		--output filename.mhd
	 */

	array_float* scales = array_new_float( 10 );

	LOG_INFO("Stopping %s", argv[0] );
	return EXIT_SUCCESS;
}

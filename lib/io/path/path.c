#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "util/util.h"
#include "io/path/path.h"

orion_filepath* _orion_filepath_init() {
	orion_filepath* fp;
	NEW(fp, orion_filepath);
	fp->components = array_new_str(3);
	fp->has_root_component = false;
	return fp;
}

orion_filepath* orion_filepath_new_from_string(const char* fp_string) {
	assert( NULL != fp_string );

	/* normalise the backslashes to forward slashes on Windows */
	char* fp_string_norm;
	size_t fp_len;
	safe_malloc_and_strcpy(&fp_string_norm, fp_string);
	size_t fp_string_len = strlen( fp_string );

	orion_filepath* fp = _orion_filepath_init();

	size_t norm_current_idx = 0;
	while( norm_current_idx < fp_len ) {
		if( '\\' == fp_string_norm[norm_current_idx] ) {
			fp_string_norm[norm_current_idx] == '/';
		}
		norm_current_idx++;
	}

	char*  fp_string_norm_cur_ptr = fp_string_norm;
	char*  fp_string_norm_end_ptr = strchr(fp_string_norm, '\0');

	/* check if the string is an absolute path */
	if( '/' == fp_string[0] ) {
		/* Unix specific: starts with '/',
		 * then it is an absolute path.
		 */
		fp->has_root_component = 1;
		safe_malloc_and_strcpy( &(fp->root_component), "/" );

		/* we add to the cur_ptr because we want to start
		 * splitting right after the root component */
		fp_string_norm_cur_ptr++;
	}

	while( fp_string_norm_cur_ptr < fp_string_norm_end_ptr ) {
		/* the variable into which the current segment will be copied */
		char* cur_comp_seg;

		if( '/' == *fp_string_norm_cur_ptr ) {
			/* skip past any forward slashes since they are empty
			 * components */
			fp_string_norm_cur_ptr++;
			continue;
		}

		char* comp_up_to_slash = strchr(fp_string_norm_cur_ptr , '/' );
		if( NULL == comp_up_to_slash ) {
			/* no more forward slashes, so we go up to the end */
			comp_up_to_slash = fp_string_norm_end_ptr;
		}

		/* copy up to (but not including) the next slash */
		safe_malloc_and_strncpy(cur_comp_seg,
				fp_string_norm_cur_ptr,
				comp_up_to_slash - fp_string_norm_cur_ptr - 1 );
		array_add_str( fp->components, cur_comp_seg);

		/* start right after the next slash */
		fp_string_norm_cur_ptr = comp_up_to_slash + 1;
	}

	TODO( split into components );
	WARN_UNIMPLEMENTED;
}

char* orion_filepath_base( orion_filepath* fp ) {
	TODO( copy last component );
}

char* orion_filepath_dir( orion_filepath* fp ) {
	TODO( copy all but last component );
}

void orion_filepath_free(orion_filepath* fp) {
	array_free_str( fp->components );
	if( fp->has_root_component ) {
		free( fp->root_component );
	}
	free(fp);
}

char* orion_filepath_to_string(orion_filepath* fp) {
	TODO( strcat );
	return NULL;
}

orion_filepath* orion_filepath_cat( orion_filepath* fp1, orion_filepath* fp2 ) {
	TODO( join the two paths and check if the second one is absolute or not );
}

orion_filepath* orion_filepath_sibling( orion_filepath* base, orion_filepath* relative) {
	orion_filepath* base_dir = orion_filepath_dir( base );
	orion_filepath* sibling = orion_filepath_cat( base_dir, relative );

	orion_filepath_free( base_dir );

	return sibling;
}

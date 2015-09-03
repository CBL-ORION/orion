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
	fp->root_component = NULL;
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
		fp->has_root_component = true;
		safe_malloc_and_strcpy( &(fp->root_component), "/" );

		/* we add to the cur_ptr because we want to start
		 * splitting right after the root component */
		fp_string_norm_cur_ptr++;
	}

	/* split into components */
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
		safe_malloc_and_strncpy(&cur_comp_seg,
				fp_string_norm_cur_ptr,
				comp_up_to_slash - fp_string_norm_cur_ptr );
		array_add_str( fp->components, cur_comp_seg);

		/* start right after the next slash */
		fp_string_norm_cur_ptr = comp_up_to_slash + 1;
	}

	return fp;
}

orion_filepath* orion_filepath_base( orion_filepath* fp ) {
	/* base_fp is the new filepath for the base component */
	orion_filepath* base_fp = _orion_filepath_init();
	base_fp->has_root_component = false;

	/* copy the last component into a buffer */
	size_t number_of_components = array_length_str(fp->components);
	char* last_component;
	safe_malloc_and_strcpy(&last_component,
			array_get_str( fp->components, number_of_components - 1));

	/* add that buffer to the base_fp */
	array_add_str( base_fp->components, last_component );

	/* there should only be one component in the base component */
	assert( array_length_str(base_fp->components) == 1 );

	return base_fp;
}

orion_filepath* orion_filepath_dir( orion_filepath* fp ) {
	/* dir_fp is the new filepath for the base component */
	orion_filepath* dir_fp = _orion_filepath_init();
	dir_fp->has_root_component = fp->has_root_component;

	if( fp->has_root_component ) {
		safe_malloc_and_strcpy(
			&( dir_fp->root_component ),
			fp->root_component );
	}

	/* TODO what if there are no more components? should it start
	 * using "."? See how Path::Tiny behaves. */
	/* copy all but the last component into dir_fp */
	size_t number_of_components = array_length_str(fp->components);
	for( int comp_idx = 0; comp_idx < number_of_components - 1; comp_idx++ ) {
		char* cur_component;
		safe_malloc_and_strcpy(&cur_component,
				array_get_str( fp->components, comp_idx));
		/* add that to the dir_fp */
		array_add_str( dir_fp->components, cur_component );
	}

	/* dir component should not be empty */
	assert( array_length_str(dir_fp->components) > 0 );

	return dir_fp;
}

void orion_filepath_free(orion_filepath* fp) {
	array_free_str( fp->components );
	if( fp->has_root_component ) {
		free( fp->root_component );
	}
	free(fp);
}

void orion_filepath_dump(orion_filepath* fp) {
	fprintf(stderr, "filepath [%p] : ", fp);
	size_t number_of_components = array_length_str(fp->components);
	if( fp->has_root_component ) {
		fprintf(stderr, "%s", fp->root_component);
	}
	for( int comp_idx = 0; comp_idx < number_of_components; comp_idx++ ) {
		fprintf(stderr, "%s", array_get_str(fp->components, comp_idx));
		if( comp_idx < number_of_components - 1 ) {
			fprintf(stderr, "/");
		}
	}
	fprintf(stderr, "\n");
}

char* orion_filepath_to_string(orion_filepath* fp) {
	char* fp_str;

	size_t total_strlen = 0;
	size_t total_buflen = 0;
	size_t number_of_components = array_length_str(fp->components);
	if( fp->has_root_component ) {
		total_strlen += strlen( fp->root_component );
	}
	for( int comp_idx = 0; comp_idx < number_of_components; comp_idx++ ) {
		total_strlen += strlen( array_get_str(fp->components, comp_idx) );
		if( comp_idx < number_of_components - 1 ) {
			total_strlen += 1; /* length of '/' */
		}
	}

	/* add 1 for null-terminator */
	total_buflen = total_strlen + 1;

	/* allocate space */
	NEW_COUNT(fp_str, char, total_buflen);
	fp_str[0] = '\0'; /* start off with empty string */

	/* now concatenate */
	if( fp->has_root_component ) {
		strncat( fp_str, fp->root_component, total_strlen );
	}
	for( int comp_idx = 0; comp_idx < number_of_components; comp_idx++ ) {
		strncat( fp_str, array_get_str(fp->components, comp_idx), total_strlen );
		if( comp_idx < number_of_components - 1 ) {
			strncat( fp_str, "/", total_strlen );
		}
	}

	return fp_str;
}

orion_filepath* orion_filepath_cat( orion_filepath* fp1, orion_filepath* fp2 ) {
	orion_filepath* cat_fp = _orion_filepath_init();
	TODO( check if the second one is absolute or not );
	if( fp1->has_root_component ) {
		cat_fp->has_root_component = true;
		safe_malloc_and_strcpy(
			&(cat_fp->root_component),
			fp1->root_component );
	}

	orion_filepath* fp[] = { fp1, fp2 };

	for( size_t fp_idx = 0; fp_idx < 2; fp_idx++ ) {
		size_t number_of_components = array_length_str(fp[fp_idx]->components);
		for( int comp_idx = 0; comp_idx < number_of_components; comp_idx++ ) {
			char* cur_component;
			safe_malloc_and_strcpy(&cur_component,
					array_get_str( fp[fp_idx]->components, comp_idx));
			array_add_str( cat_fp->components, cur_component );
		}
	}

	return cat_fp;
}

orion_filepath* orion_filepath_sibling( orion_filepath* base, orion_filepath* relative) {
	orion_filepath* base_dir = orion_filepath_dir( base );
	orion_filepath* sibling = orion_filepath_cat( base_dir, relative );

	orion_filepath_free( base_dir );

	return sibling;
}

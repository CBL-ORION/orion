#include "eig_feat_result.h"

#include "util/mem.h"

orion_eig_feat_result* orion_eig_feat_result_new() {
	orion_eig_feat_result* res;
	NEW(res, orion_eig_feat_result);
	res->eig_feat = NULL;
	return res;
}

void orion_eig_feat_result_free(orion_eig_feat_result* e) {
	if( e->eig_feat ) {
		for( size_t a_idx = 0; a_idx < array_length_ndarray3(e->eig_feat); a_idx++) {
			ndarray3_free( array_get_ndarray3(e->eig_feat, a_idx) );
		}
		array_free_ndarray3(e->eig_feat);
	}

	free(e);
}

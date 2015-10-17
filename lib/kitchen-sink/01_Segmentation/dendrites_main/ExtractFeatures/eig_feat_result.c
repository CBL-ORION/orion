#include "eig_feat_result.h"

#include "util/mem.h"
#include "simple-log/simplelog.h"

orion_eig_feat_result* orion_eig_feat_result_new() {
	orion_eig_feat_result* res;
	NEW(res, orion_eig_feat_result);
	res->eig_feat = NULL;
	return res;
}

void orion_eig_feat_result_free(orion_eig_feat_result* e) {
	if( e->eig_feat ) {
		size_t a_len = array_length_ndarray3(e->eig_feat);
		for( size_t a_idx = 0; a_idx < a_len; a_idx++) {
			ndarray3* n = array_get_ndarray3(e->eig_feat, a_idx);
			/*[>DEBUG<]LOG_DEBUG("Free data from ndarray3 (%p) at (%p)", n, n->p);*/
			ndarray3_free( n );
		}
		array_free_ndarray3(e->eig_feat);
	}

	free(e);
}

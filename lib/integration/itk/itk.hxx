#ifndef INTEGRATION_ITK_H
#define INTEGRATION_ITK_H 1

/* internal containers */
#include "ndarray/array_ndarray3.h"
#include "ndarray/ndarray3.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern array_ndarray3* orion_filter_method_sato( ndarray3* vol, float sigma );
extern array_ndarray3* orion_filter_method_frangi( ndarray3* vol, float sigma );
extern array_ndarray3* orion_filter_method_single_eigenvalue( ndarray3* vol, float sigma );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INTEGRATION_ITK_H */


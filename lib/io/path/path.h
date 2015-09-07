#ifndef IO_PATH_PATH_H
#define IO_PATH_PATH_H 1

#include <stdbool.h>

#include "container/array.h"

typedef struct {
	/* A list of components of the path.
	 *
	 * May either refer to
	 *   - an absolute path (if has_root_component == true) or
	 *   - a relative path (if has_root_component == false).
	 */
	array_str* components;

	bool has_root_component;
	/* root part of the path:
	 * - On Unix: "/"
	 * - On Windows: C:/, D:/, etc.
	 *
	 * This is only used if has_root_component == true.
	 *
	 * Must end in in the file separator ("/").
	 */
	char* root_component;
} orion_filepath;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern orion_filepath* orion_filepath_new_from_string(const char* fp_string);
extern void orion_filepath_free(orion_filepath* fp);

extern void orion_filepath_dump(orion_filepath* fp);
extern char* orion_filepath_to_string(orion_filepath* fp);

extern orion_filepath* orion_filepath_base( orion_filepath* fp );
extern orion_filepath* orion_filepath_dir( orion_filepath* fp );

extern orion_filepath* orion_filepath_sibling( orion_filepath* base, orion_filepath* relative);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* IO_PATH_PATH_H */

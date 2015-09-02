#ifndef IO_PATH_PATH_H
#define IO_PATH_PATH_H 1

#include <stdbool.h>

#include "container/array.h"

typedef struct {
	array_str* components;

	bool has_root_component;
	char* root_component;
} orion_filepath;
extern orion_filepath* orion_filepath_new_from_string(const char* fp_string);
extern void orion_filepath_dump(orion_filepath* fp);
extern char* orion_filepath_to_string(orion_filepath* fp);

extern orion_filepath* orion_filepath_base( orion_filepath* fp );
extern orion_filepath* orion_filepath_dir( orion_filepath* fp );

extern orion_filepath* orion_filepath_sibling( orion_filepath* base, orion_filepath* relative);

#endif /* IO_PATH_PATH_H */

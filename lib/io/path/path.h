#ifndef IO_PATH_PATH_H
#define IO_PATH_PATH_H 1

typedef struct {
	char** components;
	size_t number_of_components;
} orion_filepath;

extern orion_filepath* orion_filepath_new_from_string(const char* fp_string);
extern char* orion_filepath_to_string(orion_filepath* fp);

#endif /* IO_PATH_PATH_H */

#ifndef ORION3_CONFIG_PARSER_H
#define ORION3_CONFIG_PARSER_H 1

#include <assert.h>

#include "param/param.h"
#include "simple-log/simplelog.h"

extern orion3_param* orion3_param_read_input_file(char* filename);

#endif

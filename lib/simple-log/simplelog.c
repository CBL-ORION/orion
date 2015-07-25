#include "simplelog.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


void LOG_FORMAT(const char* tag, const char* message, va_list args) {
	time_t now;
	time(&now);
	char* date = ctime(&now);
	date[strlen(date) - 1] = '\0';
	fprintf(SIMPLE_LOG_FILE, "%s [%s] ", date, tag);
	vfprintf(SIMPLE_LOG_FILE, message, args);
	fprintf(SIMPLE_LOG_FILE, "\n");
}

#define LOG_TAG_FUNCTION(X)  \
	void LOG_## X(const char* message, ...) { \
		va_list args; \
		va_start(args, message); \
		LOG_FORMAT( # X , message, args); \
		va_end(args); \
	}

LOG_TAG_FUNCTION(ERROR);
LOG_TAG_FUNCTION(INFO);
LOG_TAG_FUNCTION(DEBUG);

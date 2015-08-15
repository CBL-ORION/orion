#include "simplelog.h"

void LOG_FORMAT(const char* tag, const char* message, va_list args) {
	time_t now;
	time(&now);
	char* date = ctime(&now);
	date[strlen(date) - 1] = '\0';
	fprintf(SIMPLE_LOG_FILE, "%s [%s] ", date, tag);
	vfprintf(SIMPLE_LOG_FILE, message, args);
	fprintf(SIMPLE_LOG_FILE, "\n");
}

#define LOG_FUNCTION_NAME(TYPE_OF_LOG_MESSAGE)  LOG_ ## TYPE_OF_LOG_MESSAGE

#define LOG_TAG_FUNCTION(X)  \
	void LOG_FUNCTION_NAME(X)(const char* message, ...) { \
		va_list args; \
		va_start(args, message); \
		LOG_FORMAT( STRINGIZE(X) , message, args); \
		va_end(args); \
	}

LOG_TAG_FUNCTION(ERROR);
LOG_TAG_FUNCTION(INFO);
LOG_TAG_FUNCTION(DEBUG);

#undef LOG_FUNCTION_NAME
#undef LOG_TAG_FUNCTION

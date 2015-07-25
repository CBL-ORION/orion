#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H

#define SIMPLE_LOG_FILE stderr

void LOG_ERROR(const char* message, ...);
void LOG_INFO (const char* message, ...);
void LOG_DEBUG(const char* message, ...);

#endif /* SIMPLE_LOG_H */

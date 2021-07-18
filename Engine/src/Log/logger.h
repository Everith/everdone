#pragma once

#define EERROR 1 
#define EWARNING 1
#define EINFO 1

typedef enum log_level {
	Fatal = 0,
	Error = 1,
	Warning = 2,
	Info = 3
}log_level;

char initialize_logging();
void close_logging();

void log_output(log_level level, const char* message, ...);

#define EVE_FATAL(message, ...)	log_output(Fatal, message, ##__VA_ARGS__)
#define EVE_ERROR(message, ...) log_output(Error, message, ##__VA_ARGS__)

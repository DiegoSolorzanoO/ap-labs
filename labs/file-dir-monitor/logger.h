// Logger

#ifndef LOGGER_H_
#define LOGGER_H_

int initLogger(char *logType);

int infof(const char *format, ...);

int warnf(const char *format, ...);

int errorf(const char *format, ...);

int panicf(const char *format, ...);

#endif
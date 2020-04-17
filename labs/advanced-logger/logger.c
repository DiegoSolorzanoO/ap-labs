// Diego Solorzano Ortiz

#include <stdarg.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include "logger.h"

int syslogging = 0;

void textcolor(int attr, int fg, int bg) {	
    char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int infof(const char *format, ...) {
    va_list arguments;
    textcolor(0, 4, 0);
    va_start(arguments, format);
    if (syslogging==1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, arguments);
        closelog();
    }
    else
    {
        vprintf(format, arguments);
    }
    va_end(arguments);
    textcolor(0,7,0);
    if (syslogging==0){ printf("\n"); }
    return 0;	
}

int warnf(const char *format, ...) {
    va_list arguments;
    textcolor(0, 3, 0);
    va_start(arguments, format);
    if (syslogging==1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, arguments);
        closelog();
    }
    else
    {
        vprintf(format, arguments);
    }
    va_end(arguments);
    textcolor(0,7,0);
    if (syslogging==0){ printf("\n"); }
    return 0;	
}

int errorf(const char *format, ...) {
    va_list arguments;
    textcolor(0, 1, 0);
    va_start(arguments, format);
    if (syslogging==1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, arguments);
        closelog();
    }
    else
    {
        vprintf(format, arguments);
    }
    va_end(arguments);
    textcolor(0,7,0);
    if (syslogging==0){ printf("\n"); }
    return 0;	
}

int panicf(const char *format, ...) {
    va_list arguments;
    textcolor(0, 5, 0);
    va_start(arguments, format);
    if (syslogging==1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, arguments);
        closelog();
    }
    else
    {
        vprintf(format, arguments);
    }
    va_end(arguments);
    textcolor(0,7,0);
    if (syslogging==0){ printf("\n"); }
    return 0;	
}

int initLogger(char *logType) {
    printf("Initializing Logger on: %s\n", logType);
    if (strcmp(logType,"stdout")==0)
    {
        syslogging = 0;
    }
    else
    {
        if (strcmp(logType,"syslog")==0)
        {
            syslogging = 1;
        }
        else
        {
            printf("Error al seleccionar logger");
            return 0;
        }
        
    }
    
    return 0;
}

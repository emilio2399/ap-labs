#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <syslog.h>
#include "logger.h"

int logN = 0;

int initLogger(char *logType) {
    printf("Log mode changed to %s\n", logType);

    if (strcmp(logType,"stdout") == 0){
        logN = 0;
    } else {
        if (strcmp(logType,"syslog") == 0)
        {
            logN = 1;
        }
        else
        {
            printf("ERROR: NON VALID LOGGER");
            return -1;
        }
        
    }
    
    return 0;
}


int infof ( const char * format, ... )
{
    //time
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    char *timeStr= asctime(timeinfo);
    timeStr[strlen(timeStr)-1] = 0;

    //color
    printf("\x1b[34m");


    //arguments
    va_list args;
    va_start (args, format);

    if(logN == 1){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, args);
        closelog();

    } else {
        printf("INFO[%s]: ",timeStr);
        vprintf (format, args);
        printf("\n");
    }


    va_end (args);

    printf("\x1b[0m");
    
    return 1;
}

int warnf ( const char * format, ... )
{
    //time
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    char *timeStr= asctime(timeinfo);
    timeStr[strlen(timeStr)-1] = 0;

    //color
    printf("\x1b[33m");

    //arguments
    va_list args;
    va_start (args, format);

    if(logN == 1){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, args);
        closelog();

    } else {
        printf("WARN[%s]: ",timeStr);
        vprintf (format, args);
        printf("\n");
    }

    va_end (args);

    printf("\x1b[0m");
    
    return 1;
}

int errorf ( const char * format, ... )
{
    //time
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    char *timeStr= asctime(timeinfo);
    timeStr[strlen(timeStr)-1] = 0;

    //color
    printf("\x1b[31m");

    //arguments
    va_list args;
    va_start (args, format);

    if(logN == 1){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, args);
        closelog();

    } else {
        printf("ERROR[%s]: ",timeStr);
        vprintf (format, args);
        printf("\n");
    }

    va_end (args);

    printf("\x1b[0m");
    
    return 1;
}

int panicf ( const char * format, ... )
{
    //time
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    char *timeStr= asctime(timeinfo);
    timeStr[strlen(timeStr)-1] = 0;

    //color
    printf("\x1b[35m");

    //arguments
    va_list args;
    va_start (args, format);

    if(logN == 1){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG,format, args);
        closelog();

    } else {
        printf("PANIC[%s]: ",timeStr);
        vprintf (format, args);
        printf("\n");
    }

    va_end (args);

    printf("\x1b[36m");
    
    return 1;
}

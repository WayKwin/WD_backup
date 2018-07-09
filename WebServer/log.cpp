#include "log.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include<fcntl.h>

Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

void Logger::AddToQueue(const char* pszLevel, const char* pszFile, int lineNo, const char* pszFuncSig, char* pszFmt, ...)
{
    char msg[256] = { 0 };

    va_list vArgList;                            
    va_start(vArgList, pszFmt);
    vsnprintf(msg, 256, pszFmt, vArgList);
    va_end(vArgList);

    time_t now = time(NULL);
    struct tm* tmstr = localtime(&now);
    sprintf(content, "[%04d-%02d-%02d %02d:%02d:%02d][%s][0x%04lu][%s:%d %s]%s\n",
                tmstr->tm_year + 1900,
                tmstr->tm_mon + 1,
                tmstr->tm_mday,
                tmstr->tm_hour,
                tmstr->tm_min,
                tmstr->tm_sec,
                pszLevel,
                pthread_self(),
                pszFile,
                lineNo,
                pszFuncSig,
                msg);
    process(pszLevel);
}

void Logger::process(const char* pszLevel)
{
        //log_file_info(  ) ;
        if(strcmp(pszLevel,"INFO"))
        log_file_info = open(log_info,O_RDWR|O_CREAT|O_APPEND,0666);

        else if(strcasecmp(pszLevel,"Waring"))
        log_file_info = open(log_warning,O_RDWR|O_CREAT|O_APPEND,0666);

        else if(strcasecmp(pszLevel,"ERROR"))
        log_file_info = open(log_error,O_RDWR|O_CREAT|O_APPEND,0666);

        write(log_file_info,content,strlen(content));
}

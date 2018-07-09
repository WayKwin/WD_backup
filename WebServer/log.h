
/** * 日志类头文件, Logger.h * zhangyl 2017.02.28 **/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>
#include <thread>
#include "locker.h"
#include <mutex>
#include <condition_variable>
#include <list>
#include<string.h>

//struct FILE;


#define LogInfo(...) Logger::GetInstance().AddToQueue("INFO", __FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define LogWarning(...) Logger::GetInstance().AddToQueue("WARNING", __FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define LogError(...) Logger::GetInstance().AddToQueue("ERROR", __FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)

  const static char* log_info= "./log/LogInfo.log";
  const static char* log_warning= "./log/LogWaring.log";
  const static char* log_error= "./log/LogError.log";
class Logger
{
public:

    static Logger& GetInstance();


   void AddToQueue(const char* pszLevel, const char* pszFile, int lineNo, const char* pszFuncSig, char* pszFmt, ...);
  
    void process(const char* pszLevel);

private:
    Logger() = default;
    Logger(const Logger& rhs) = delete;
    Logger& operator =(Logger& rhs) = delete;



private:
    int            log_file_info;
    int            log_file_error;
    int            log_file_warning;
    char content[512] = { 0 };
    //locker         log_lock;
    //sem            log_sem;            //有新的日志到来的标识
};

#endif //!__LOGGER_H__
/** * 日志类实现文件, Logger.cpp * zhangyl 2017.02.28 **/
//class LoggerInfo
//{

//}

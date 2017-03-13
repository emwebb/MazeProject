#ifndef logger_hpp
#define logger_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
typedef enum {
    INFO,
    WARNING,
    ERROR
} log_level;

void init_log();
void log(log_level level, std::string tag, std::string log);
void logi(std::string tag, std::string log);
void logw(std::string tag, std::string log);
void loge(std::string tag, std::string log);

#endif /* logger_hpp */

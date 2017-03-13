#include "logger.hpp"
std::ofstream log_file;

void init_log() {
    //Initialise the logger and set the file name.
    std::string file_name;
    
    std::time_t current_time = std::time(NULL);
    struct tm *local_time = std::localtime(&current_time);
    
    file_name += "maze_game";
    file_name += "_" + std::to_string(local_time->tm_year + 1900) + "." + std::to_string(local_time->tm_mon + 1) + "." + std::to_string(local_time->tm_mday) + "_";
    file_name += std::to_string(local_time->tm_hour) + "." + std::to_string(local_time->tm_min) + "." + std::to_string(local_time->tm_sec);
    file_name += ".log";
    log_file = std::ofstream(file_name,std::ios_base::out | std::ios_base::app);
}
void log(log_level level, std::string tag, std::string log_s) {
    
    //Format the message and send it to COUT out the log file.
    std::string message;
    std::time_t current_time = std::time(NULL);
    struct tm *local_time = std::localtime(&current_time);
    message += "[" + std::to_string(local_time->tm_year + 1900) + "/" + std::to_string(local_time->tm_mon + 1) + "/" + std::to_string(local_time->tm_mday) + " ";
    message += std::to_string(local_time->tm_hour) + ":" + std::to_string(local_time->tm_min) + ":" + std::to_string(local_time->tm_sec) + "]";
    std::string level_s;
    switch (level) {
        case INFO:
            level_s = "INFO";
            break;
        case WARNING:
            level_s = "WARNING";
            break;
        case ERROR:
            level_s = "ERROR";
            break;
            
        default:
            level_s = "UNKNOWN";
            break;
    }
    
    message += "[" + level_s + "]";
    message += "[" + tag + "]";
    message += " " + log_s;
    log_file << message << std::endl;
    std::cout << message << std::endl;
    
    
}
void logi(std::string tag, std::string log_s) {
    log(INFO,tag,log_s);
}
void logw(std::string tag, std::string log_s){
    log(WARNING,tag,log_s);
}

void loge(std::string tag, std::string log_s){
    log(ERROR,tag,log_s);
}

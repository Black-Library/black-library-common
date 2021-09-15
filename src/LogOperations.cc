/**
 * LogOperations.cc
 */

#include <string.h>

#include <algorithm>
#include <iostream>

#include <LogOperations.h>

#include <spdlog/sinks/rotating_file_sink.h>

namespace black_library {

namespace core {

namespace common {

int InitLogger(const std::string &logger_name, const std::string &log_path)
{
    try
    {
        const auto complete_log_path = log_path + "/" +logger_name + ".txt";
        spdlog::rotating_logger_mt(logger_name, complete_log_path, MAX_LOG_SIZE, MAX_LOG_FILES);
    }
    catch(const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }

    return 0;
}

} // namespace common
} // namespace core
} // namespace black_library

/**
 * FileOperations.cc
 */

#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem> 
    namespace fs = std::experimental::filesystem;
#else
    error "Missing the <filesystem> header."
#endif

#include <unistd.h>

#include <iostream>
#include <regex>
#include <string>

#include <FileOperations.h>

namespace black_library {

namespace core {

namespace common {

// wrapper for access() that returns true if invoking user can write to path
bool CheckFilePermission(const std::string &target_path)
{
    if (access(target_path.c_str(), W_OK) == 0)
        return true;

    return false;
}

// wrapper for std::filesystem::exists
bool Exists(const std::string &target_path)
{
    return fs::exists(target_path);
}

size_t GetBindIndex(const std::string &file_name)
{
    if (file_name.empty())
        return 0;

    auto first_pos = file_name.find_last_of("_");
    auto second_pos = file_name.find_last_of('.');

    if (first_pos == std::string::npos || second_pos == std::string::npos)
        return 0;

    auto temp_string = file_name.substr(first_pos, second_pos - first_pos);

    first_pos = temp_string.find_last_not_of("0123456789");

    temp_string = temp_string.substr(first_pos + 1, temp_string.size());

    return std::stoull(temp_string);
}

size_t GetChapterIndex(const std::string &file_name)
{
    if (file_name.empty())
        return 0;

    auto first_pos = file_name.find_first_of("0123456789");
    auto second_pos = file_name.find_first_of('_');

    if (first_pos == std::string::npos || second_pos == std::string::npos)
        return 0;

    auto temp_string = file_name.substr(first_pos, second_pos);

    return std::stoull(temp_string);
}

std::vector<std::string> GetFileList(const std::string &target_path)
{
    return GetFileList(target_path, "*");
}

// wrapper for std::filesystem list directorty contents
std::vector<std::string> GetFileList(const std::string &target_path, const std::string &regex_string)
{
    std::vector<std::string> file_list;

    if (!Exists(target_path))
        return file_list;

    try
    {
        const std::regex regex(regex_string, std::regex::extended); // POSIX
        for (const auto & entry : fs::directory_iterator(target_path))
        {
            const auto file_name = entry.path().filename().string();

            if (std::regex_search(file_name, regex))
            {
                file_list.emplace_back(file_name);
            }
        }
    }
    catch (std::regex_error &e)
    {
        std::cout << "Error: regex failed" << std::endl;
    }

    return file_list;
}

// wrapper for std::filesystem::create_directories
bool MakeDirectories(const std::string &target_path)
{
    if (fs::exists(target_path))
    {
        return true;
    }

    return fs::create_directories(target_path);
}

} // namespace common
} // namespace core
} // namespace black_library

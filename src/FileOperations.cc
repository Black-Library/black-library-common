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

#include <regex>

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

// wrapper for std::filesystem list directorty contents
std::vector<std::string> GetFileList(const std::string &target_path)
{
    std::vector<std::string> file_list;
    const std::regex regex("CH*");

    if (!Exists(target_path))
        return file_list;

    for (const auto & entry : fs::directory_iterator(target_path))
    {
        const auto file_name = entry.path().filename().string();

        if (std::regex_search(file_name, regex))
        {
            file_list.emplace_back(file_name);
        }
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

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

#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

#include <FileOperations.h>

#include <openssl/md5.h>

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
bool FileExists(const std::string &target_path)
{
    return fs::exists(target_path);
}

bool FileExistsAndPermission(const std::string &target_path)
{
    return FileExists(target_path) && CheckFilePermission(target_path);
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

std::string GetMD5Hash(const std::string &target_path)
{
    if (target_path.empty())
        return "";

    if (!FileExists(target_path))
        return "";

    std::string file_contents;
    std::ostringstream oss;
    unsigned char result[MD5_DIGEST_LENGTH];

    std::ifstream input_file(target_path, std::ios::in | std::ios::binary);

    if (!input_file)
        return "";

    input_file.seekg(0, std::ios::end);
    file_contents.resize(input_file.tellg());
    input_file.seekg(0, std::ios::beg);
    input_file.read(&file_contents[0], file_contents.size());
    input_file.close();

    MD5((unsigned char*)file_contents.c_str(), file_contents.size(), result);

    oss << std::hex << std::setfill('0');
    for (auto c : result) oss << std::setw(2) << (int)c;

    return oss.str();
}

size_t GetSectionIndex(const std::string &file_name)
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

    if (!FileExists(target_path))
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

// wrapper for std::filesystem::remove
bool RemoveFile(const std::string &target_path)
{
    return fs::remove(target_path);
}

std::string SanitizeFileName(const std::string &file_name)
{
    std::string sanatized_file_name = file_name;
    const std::string unallowed = " /\\*?<>:;=[]!@|.,%#'\"";

    while (sanatized_file_name.front() == '-')
    {
        sanatized_file_name.erase(sanatized_file_name.begin());
    }

    while (sanatized_file_name.back() == '-' && sanatized_file_name.size() > 0)
    {
        sanatized_file_name.pop_back();
    }

    std::transform(sanatized_file_name.begin(), sanatized_file_name.end(), sanatized_file_name.begin(),
    [&unallowed](char ch)
    {
        return (std::find(unallowed.begin(), unallowed.end(), ch) != unallowed.end()) ? '-' : ch;
    });

    const std::string dup_string = "--";

    size_t pos = sanatized_file_name.find(dup_string);

    while (pos != std::string::npos)
    {
        sanatized_file_name.replace(pos, dup_string.size(), "-");
        pos = sanatized_file_name.find(dup_string);
    }

    if (sanatized_file_name.back() == '-')
        sanatized_file_name.pop_back();

    return sanatized_file_name;
}

std::string SanitizeFilePath(const std::string &file_name)
{
    std::string sanatized_file_name = file_name;
    const std::string unallowed = " *?<>:;=[]!@|";

    if (sanatized_file_name.front() == '-')
    {
        sanatized_file_name.erase(sanatized_file_name.begin());
    }

    std::transform(sanatized_file_name.begin(), sanatized_file_name.end(), sanatized_file_name.begin(),
    [&unallowed](char ch)
    {
        return (std::find(unallowed.begin(), unallowed.end(), ch) != unallowed.end()) ? '-' : ch;
    });

    return sanatized_file_name;
}

} // namespace common
} // namespace core
} // namespace black_library

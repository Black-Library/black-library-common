/**
 * FileOperations.h
 */

#ifndef __BLACK_LIBRARY_CORE_COMMON_FILE_OPERATIONS_H__
#define __BLACK_LIBRARY_CORE_COMMON_FILE_OPERATIONS_H__

#include <string>
#include <vector>

namespace black_library {

namespace core {

namespace common {

bool CheckFilePermission(const std::string &target_path);
bool Exists(const std::string &target_path);
std::vector<std::string> GetFileList(const std::string &target_path);
bool MakeDirectories(const std::string &target_path);

} // namespace common
} // namespace core
} // namespace black_library

#endif

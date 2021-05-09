/**
 * FileOperations.h
 */

#ifndef __BLACK_LIBRARY_CORE_COMMON_FILE_OPERATIONS_H__
#define __BLACK_LIBRARY_CORE_COMMON_FILE_OPERATIONS_H__

#include <string>

namespace black_library {

namespace core {

namespace common {

bool CheckFilePermission(const std::string &target_path);
bool MakeDirectories(const std::string &target_path);

} // namespace common
} // namespace core
} // namespace black_library

#endif

/**
 * FileOperations.cc
 */

#include <unistd.h>

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

} // namespace common
} // namespace core
} // namespace black_library

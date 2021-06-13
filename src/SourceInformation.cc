/**
 * SourceInformation.cc
 */

#include <string.h>

#include <StringOperations.h>

#include <SourceInformation.h>

namespace black_library {

namespace core {

namespace common {

bool SourceInformationMember(const std::string &url)
{
    bool is_member = false;

    if (ContainsString(url, AO3::source_url))
    {
        is_member = true;
    }
    else if (ContainsString(url, FFN::source_url))
    {
        is_member = true;
    }
    else if (ContainsString(url, SBF::source_url))
    {
        is_member = true;
    }
    else if (ContainsString(url, RR::source_url))
    {
        is_member = true;
    }

    return is_member;
}

} // namespace common
} // namespace core
} // namespace black_library

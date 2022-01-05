set(SPDLOG_BUILD_SHARED ON)
set(SPDLOG_INSTALL ON)

# nlohmann json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)

# spdlog
add_subdirectory(spdlog)

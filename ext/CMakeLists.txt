set(SPDLOG_BUILD_SHARED ON)
set(SPDLOG_INSTALL ON)

# catch2
add_subdirectory(catch2)

# nlohmann json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)

# spdlog
add_subdirectory(spdlog)

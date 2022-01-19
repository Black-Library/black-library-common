# catch2
add_subdirectory(catch2)

# nlohmann json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)

# spdlog
set(SPDLOG_BUILD_SHARED ON CACHE INTERNAL "Build spdlog shared library")
set(SPDLOG_INSTALL ON CACHE INTERNAL "Install spdlog")
message(STATUS "SPDLOG_BUILD_SHARED: ${SPDLOG_BUILD_SHARED}")
message(STATUS "SPDLOG_INSTALL: ${SPDLOG_INSTALL}")
add_subdirectory(spdlog)

add_library(jconfig JConfig.cpp)
add_dependencies(jconfig nlohmann spdlog)
target_include_directories(jconfig INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ )
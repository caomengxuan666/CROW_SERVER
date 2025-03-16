cmake_minimum_required(VERSION 3.15)

project(Diabetes-server LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 查找crow库
find_package(Crow CONFIG REQUIRED)

# 添加子目录
add_subdirectory(src)

# 安装目录为当前目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})


# 安装规则
install(TARGETS Diabetes-server DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/dll/linux64/ DESTINATION lib)

# 启用测试支持
enable_testing()

# 添加测试
add_subdirectory(test)

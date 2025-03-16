cmake_minimum_required(VERSION 3.15)

project(Diabetes-server LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 如果是windows,设置vcpkg toolchain的路径
if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
    #设置cmake-prefix_path
    set(CMAKE_PREFIX_PATH "D:/vcpkg/installed/x64-mingw-dynamic")
endif ()

# 查找crow库
find_package(Crow CONFIG REQUIRED)

# 添加子目录
add_subdirectory(src)

# 安装目录为当前目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(test)

# 安装规则
install(TARGETS Diabetes-server DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/dll/linux64/ DESTINATION lib)

# 启用测试支持
enable_testing()

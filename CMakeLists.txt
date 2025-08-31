cmake_minimum_required(VERSION 3.15)

project(Diabetes-server LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 如果是windows,设置vcpkg toolchain的路径
if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
    #设置cmake-prefix_path
    set(CMAKE_PREFIX_PATH "D:/vcpkg/vcpkg-master/installed/x64-windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0A00")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
    endif ()

endif ()

# 查找crow库
find_package(Crow CONFIG REQUIRED)

# 添加子目录
add_subdirectory(src)

function(copy_resources)
#将根目录下的debug.cfg移到build/src/controller下
    file(COPY debug.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/controller)
    message(STATUS "copy debug.cfg to ${CMAKE_CURRENT_BINARY_DIR}/src/controller")
    file(COPY debug.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/service)
endfunction()

copy_resources()

# 安装目录为当前目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(test)

# 安装规则
install(TARGETS Diabetes-server DESTINATION bin)
if (WIN32)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/dll/ DESTINATION bin)
else()
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/dll/linux64/ DESTINATION lib)
endif()

# 启用测试支持
enable_testing()

# CPack配置
set(CPACK_PACKAGE_NAME "DiabetesServer")
set(CPACK_PACKAGE_VENDOR "PESONAL DEVELOPER CMX")
set(CPACK_PACKAGE_DESCRIPTION "A C++ server application based on Crow framework for infrared image acquisition")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")

# Windows特定配置
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
    
    # Windows安装程序配置
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    
    # 创建开始菜单快捷方式
    set(CPACK_PACKAGE_EXECUTABLES "Diabetes-server" "Diabetes Server")
    set(CPACK_CREATE_DESKTOP_LINKS "Diabetes-server")
endif()

# Linux特定配置
if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
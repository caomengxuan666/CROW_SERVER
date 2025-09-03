cmake_minimum_required(VERSION 3.15)

project(Diabetes-server LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ASIO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/asio/asio/include)
set(asio_FOUND TRUE)
# 避免 Findasio.cmake 再去瞎找
set(asio_INCLUDE_DIR ${ASIO_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/asio/asio/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party)
# 添加子目录
add_subdirectory(src)

add_subdirectory(third_party/crow)

function(copy_resources)
#将根目录下的debug.cfg移到build/src/controller下
    file(COPY debug.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/controller)
    message(STATUS "copy debug.cfg to ${CMAKE_CURRENT_BINARY_DIR}/src/controller")
    file(COPY debug.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/service)
    file(COPY crow_server.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/controller)
    message(STATUS "copy crow_server.ini to ${CMAKE_CURRENT_BINARY_DIR}/src/controller")
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
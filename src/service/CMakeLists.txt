# 根据平台设置GAODESDK库
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(GAODESDK GuideSDK MeasureStream ParseGWImage avcodec avformat avutil swscale usb-1.0 va-drm va-x11)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(GAODESDK GuideSDK GFileAnalysis PocoFoundation PocoJSON avcodec-58 avdevice-58 avfilter-7 avformat-58 avutil-56 swresample-3 swscale-5)
endif()

# 添加共享库
add_library(ServiceManager STATIC ServiceManager.cpp)

# 设置通用前缀
set(SDK_PREFIX "${CMAKE_SOURCE_DIR}/dll/")

# 根据不同的平台选择具体的子目录
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # Linux 64-bit
    set(SDK_SUBDIR "linux64")
    message(STATUS "Linux 64-bit")
    message("SDK prefix: ${SDK_PREFIX}${SDK_SUBDIR}")
  else()
    # Linux 32-bit
    set(SDK_SUBDIR "linux32")
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # Windows 64-bit
    set(SDK_SUBDIR "win64")
  else()
    # Windows 32-bit
    set(SDK_SUBDIR "win32")
  endif()
endif()

# 设置链接目录和库
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_directories(ServiceManager PUBLIC
                          ${SDK_PREFIX}${SDK_SUBDIR})

  # 确保运行时路径支持
  set_target_properties(ServiceManager PROPERTIES
                        BUILD_WITH_INSTALL_RPATH TRUE
                        INSTALL_RPATH "${SDK_PREFIX}${SDK_SUBDIR}"
                        SKIP_BUILD_RPATH FALSE
                        INSTALL_RPATH_USE_LINK_PATH TRUE)
else()
  target_link_directories(ServiceManager PUBLIC
                          ${SDK_PREFIX}${SDK_SUBDIR})
endif()

# 链接静态库
target_link_libraries(ServiceManager PUBLIC Crow::Crow)

#如果是windows,额外链接winsock2
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(ServiceManager PUBLIC ws2_32 wsock32)
endif()

# 链接动态库

#如果是linux,链接.so
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  foreach(LIB ${GAODESDK})
    target_link_libraries(ServiceManager PUBLIC ${SDK_PREFIX}${SDK_SUBDIR}/lib${LIB}.so)
  endforeach()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  foreach(LIB ${GAODESDK})
    target_link_libraries(ServiceManager PUBLIC ${SDK_PREFIX}${SDK_SUBDIR}/${LIB}.dll)
  endforeach()
  # 根据构建类型选择正确的 PortingMod 库链接
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(ServiceManager PUBLIC ${SDK_PREFIX}${SDK_SUBDIR}/PortingMod_Debug_x64.lib)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(ServiceManager PUBLIC ${SDK_PREFIX}${SDK_SUBDIR}/PortingMod_Release_x64.lib)
  endif()
  # 添加对 C 标准库和 C++ 标准库的链接
  target_link_libraries(ServiceManager PUBLIC msvcrt msvcprt)
endif ()

# 安装规则
install(TARGETS ServiceManager DESTINATION lib)
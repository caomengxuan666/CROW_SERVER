set(GAODESDK GuideSDK MeasureStream ParseGWImage
    avcodec avformat avutil swscale usb-1.0 va-drm va-x11)

set(GaoDeServerSRC main.cpp logHandler.hpp)

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

# 添加可执行文件
add_executable(${PROJECT_NAME} ${GaoDeServerSRC})

# 设置链接目录和库
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_directories(${PROJECT_NAME} PUBLIC
                          ${SDK_PREFIX}${SDK_SUBDIR})

  # 确保运行时路径支持
  set_target_properties(${PROJECT_NAME} PROPERTIES
                        BUILD_WITH_INSTALL_RPATH TRUE
                        INSTALL_RPATH "${SDK_PREFIX}${SDK_SUBDIR}"
                        SKIP_BUILD_RPATH FALSE
                        INSTALL_RPATH_USE_LINK_PATH TRUE)
else()
  target_link_directories(${PROJECT_NAME} PUBLIC
                          ${SDK_PREFIX}${SDK_SUBDIR})
endif()

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE ServiceManager RepositoryManager)

# 链接动态库
foreach(LIB ${GAODESDK})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${SDK_PREFIX}${SDK_SUBDIR}/lib${LIB}.so)
endforeach()

# 安装规则
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
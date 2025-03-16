set(GAODESDK GuideSDK MeasureStream ParseGWImage
    avcodec avformat avutil swscale usb-1.0 va-drm va-x11)

set(GaoDeServerSRC main.cpp logHandler.hpp)


# 添加可执行文件
add_executable(${PROJECT_NAME} ${GaoDeServerSRC})

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE ServiceManager RepositoryManager)

# 安装规则
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
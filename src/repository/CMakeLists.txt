set(GAODESDK GuideSDK MeasureStream ParseGWImage
    avcodec avformat avutil swscale usb-1.0 va-drm va-x11)

# 添加共享库
add_library(RepositoryManager STATIC RepositoryManager.cpp)

# 链接静态库
target_link_libraries(RepositoryManager PUBLIC Crow::Crow)

# 安装规则
install(TARGETS RepositoryManager DESTINATION lib)
set(GAODESDK GuideSDK MeasureStream ParseGWImage
    avcodec avformat avutil swscale usb-1.0 va-drm va-x11)

# 添加共享库
add_library(RepositoryManager STATIC RepositoryManager.cpp)

# 链接静态库
target_link_libraries(RepositoryManager PUBLIC Crow::Crow)

# 链接Utility

#如果是windows,额外链接winsock2
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(RepositoryManager PUBLIC ws2_32 )
endif()
# 安装规则
install(TARGETS RepositoryManager DESTINATION `lib)
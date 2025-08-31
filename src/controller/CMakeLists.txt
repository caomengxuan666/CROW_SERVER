set(GAODESDK GuideSDK MeasureStream ParseGWImage
    avcodec avformat avutil swscale usb-1.0 va-drm va-x11)

set(GaoDeServerSRC main.cpp logHandler.hpp)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${GaoDeServerSRC})

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE ServiceManager RepositoryManager Utility)

# 链接高德SDK相关动态库
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        ${CMAKE_SOURCE_DIR}/dll/win64/PortingMod_Release_x64.lib
        ${CMAKE_SOURCE_DIR}/dll/win64/GuideSDK.lib
        ${CMAKE_SOURCE_DIR}/dll/win64/GFileAnalysis.lib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        ${CMAKE_SOURCE_DIR}/dll/linux64/libGuideSDK.so
        ${CMAKE_SOURCE_DIR}/dll/linux64/libMeasureStream.so
        ${CMAKE_SOURCE_DIR}/dll/linux64/libParseGWImage.so)
endif()

# 链接其他系统库
target_link_libraries(${PROJECT_NAME} PRIVATE 
    avcodec avformat avutil swscale swresample avdevice
    usb-1.0 va va-drm va-x11
    PocoFoundation PocoJSON
    pthread dl)

# 安装规则
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
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
if (WIN32)
    # Windows平台只需要链接实际存在的库
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        usb-1.0 va 
        PocoFoundation PocoJSON
        )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        avcodec avformat avutil swscale swresample avdevice
        usb-1.0 va va-drm va-x11
        PocoFoundation PocoJSON
        pthread dl)
endif()

# Windows平台下将所有DLL文件复制到可执行文件目录
if (WIN32)
    file(GLOB DLL_FILES "${CMAKE_SOURCE_DIR}/dll/win64/*.dll")
    foreach(DLL_FILE ${DLL_FILES})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endforeach()
endif()

# 安装规则
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if (WIN32)
    file(GLOB INSTALL_DLL_FILES "${CMAKE_SOURCE_DIR}/dll/win64/*.dll")
    install(FILES ${INSTALL_DLL_FILES} DESTINATION bin)
else()
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/dll/linux64/ DESTINATION lib)
endif()
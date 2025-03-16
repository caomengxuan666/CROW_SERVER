set(Python_EXECUTABLE "/home/cmx/miniconda3/envs/cmx/bin/python")

# 检查 Python 解释器是否存在
if(NOT EXISTS ${Python_EXECUTABLE})
    message(FATAL_ERROR "Python interpreter not found at: ${Python_EXECUTABLE}")
else()
    message(STATUS "Python interpreter found at: ${Python_EXECUTABLE}")
endif()

# 添加 pytest 测试
add_test(NAME pytest_tests
    COMMAND ${Python_EXECUTABLE} -m pytest -v -s ${CMAKE_SOURCE_DIR}/test/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# 添加一个自定义目标运行 pytest
add_custom_target(run_pytest
    COMMAND ${Python_EXECUTABLE} -m pytest -v -s ${CMAKE_SOURCE_DIR}/test/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running pytest tests..."
)
# 默认硬编码的 Python 路径
set(Python_EXECUTABLE "/home/cmx/miniconda3/envs/cmx/bin/python")

# 允许用户手动指定 Python 解释器路径
if(DEFINED ENV{PYTHON_EXECUTABLE})
    set(Python_EXECUTABLE $ENV{PYTHON_EXECUTABLE})
endif()

# 检查 Python 解释器是否存在
if(NOT EXISTS ${Python_EXECUTABLE})
    message(STATUS "Hardcoded Python interpreter not found at: ${Python_EXECUTABLE}")
    # 使用 find_package 查找 Python 解释器
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    set(Python_EXECUTABLE ${Python3_EXECUTABLE})
    message(STATUS "Using Python interpreter found by find_package: ${Python_EXECUTABLE}")
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
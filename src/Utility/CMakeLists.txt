# 这个库面向的是repository层

add_library(Utility CsvWriter.h CsvWriter.cpp CsvExample.cpp)

add_executable(CsvExample CsvExample.cpp)
target_link_libraries(CsvExample PRIVATE Utility)
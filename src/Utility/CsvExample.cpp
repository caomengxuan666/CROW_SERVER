#include "CsvWriter.h"

#include <iostream>

int main() {
    std::vector<std::vector<std::string>> data = {
            {"Name", "Age", "City"},
            {"Alice", "25", "New York"},
            {"Bob", "30", "Los Angeles"}};

    // 修改：接收 std::pair<bool, std::string> 类型的返回值
    auto result = Utility::CsvWriter::writeCsv("output.csv", data);
    if (result.first) {
        std::cout << "CSV文件写入成功！文件路径: " << result.second << std::endl;
    } else {
        std::cout << "CSV文件写入失败！" << std::endl;
    }

    return 0;
}
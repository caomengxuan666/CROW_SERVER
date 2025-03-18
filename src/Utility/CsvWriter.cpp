#include "CsvWriter.h"
#include <filesystem> // 引入 filesystem 头文件
#include <fstream>

namespace Utility {
    std::pair<bool, std::string> CsvWriter::writeCsv(const std::string &filePath, const std::vector<std::vector<std::string>> &data) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            return {false, ""}; // 文件打开失败
        }

        for (const auto &row: data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i != row.size() - 1) {
                    file << ","; // 列之间用逗号分隔
                }
            }
            file << "\n"; // 换行
        }

        file.close();
        // 使用 std::filesystem 获取绝对路径
        return {true, std::filesystem::absolute(filePath).string()}; // 写入成功并返回绝对路径
    }
}// namespace Utility
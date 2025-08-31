/**
 * @FilePath     : /crow_server/src/Utility/CsvWriter.h
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-18 14:17:07
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/

#include <string>
#include <vector>

namespace Utility {
    class CsvWriter {
    public:
        // 静态方法：写入CSV文件，返回是否成功以及文件路径
        static std::pair<bool, std::string> writeCsv(const std::string &filePath, const std::vector<std::vector<std::string>> &data);
    };
}// namespace Utility

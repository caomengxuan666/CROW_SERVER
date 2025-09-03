/**
 * @FilePath     : /home/cmx/codespace/crow_server/src/Utility/ConfigManager.hpp
 * @Description  : 全局配置管理器，用于在其他模块中访问配置
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-09-03 20:34:43
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/

#pragma once

#include "config.hpp"

namespace crow_server {
    namespace config {
        
        // 获取全局配置的函数
        const GlobalConfig& getGlobalConfig();
        
    } // namespace config
} // namespace crow_server
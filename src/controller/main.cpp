#include "../repository/RepositoryManager.hpp"
#include "../Utility/config.hpp"
#include "../Utility/ConfigManager.hpp"
#include "routes.hpp"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <memory>

// 全局配置指针定义已在config.hpp中声明，这里只需定义
std::unique_ptr<crow_server::config::GlobalConfig> crow_server::config::g_config;

// 获取全局配置的函数定义已在ConfigManager.hpp中声明，这里提供实现
const crow_server::config::GlobalConfig& crow_server::config::getGlobalConfig() {
    if (!crow_server::config::g_config) {
        // 如果配置未初始化，则加载默认配置
        crow_server::config::g_config = std::make_unique<crow_server::config::GlobalConfig>(
                crow_server::config::GlobalConfig::load());
    }
    return *crow_server::config::g_config;
}

int main() {
    std::cout << "Starting application..." << std::endl;
    
    // 初始化默认配置文件
    std::cout << "Initializing default config..." << std::endl;
    crow_server::config::initialize_default_config();

    // 加载配置
    std::cout << "Loading config..." << std::endl;
    crow_server::config::g_config = std::make_unique<crow_server::config::GlobalConfig>(
            crow_server::config::GlobalConfig::load());

    // 打印配置信息
    std::cout << "Printing config..." << std::endl;
    crow_server::config::print_config(*crow_server::config::g_config);
    
    std::cout << "Creating RouteManager..." << std::endl;
    routes::RouteManager routeManager;
    
    std::cout << "Running RouteManager..." << std::endl;
    routeManager.run();
    
    std::cout << "Application finished." << std::endl;
    return 0;
}
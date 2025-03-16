/**
 * @FilePath     : /crow_server/src/main.cpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-15 20:27:18
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#include "routes.hpp"
int main() {
    routes::RouteManager routeManager;
    routeManager.run();
}
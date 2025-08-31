#include "../repository/RepositoryManager.hpp"
#include "routes.hpp"
#include <csignal>
#include <cstdlib>

int main() {
    routes::RouteManager routeManager;
    routeManager.run();
}
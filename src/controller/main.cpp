#include "routes.hpp"
#include <csignal>
#include <cstdlib>
#include "../repository/RepositoryManager.hpp"

int main() {
    routes::RouteManager routeManager;
    routeManager.run();
}
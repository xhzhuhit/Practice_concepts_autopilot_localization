#include "../include/global.config.hpp"

int main() {
    bool flag = GlobalConfig::getInstance()->say_hello();
    return 0;
}

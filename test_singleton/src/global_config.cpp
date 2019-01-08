#include "../include/global.config.hpp"

GlobalConfig* GlobalConfig::_s_instance = new GlobalConfig();

GlobalConfig::GlobalConfig() {

}

GlobalConfig* GlobalConfig::getInstance() {
    return _s_instance;
}

bool GlobalConfig::say_hello() {
    std::cout << "Baby, you are great!" << std::endl;
    return true;
}

#ifndef GLOBAL_CONFIG_HPP
#define GLOBAL_CONFIG_HPP
#include <iostream>
#include <string>
#include <vector>

class GlobalConfig {
public:
    static GlobalConfig* getInstance();
    bool say_hello();
private:
    GlobalConfig();

private:
    static GlobalConfig* _s_instance;

};

#endif

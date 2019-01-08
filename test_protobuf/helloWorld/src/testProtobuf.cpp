#include "../proto/hello.pb.h"
#include <iostream>

int main() {
    //Person<double> pose(1.5, 2,5);
    std::cout << "at start" << std::endl;
    tutorial::Person person;
    std::cout << "at start" << std::endl;
    double pname = 1.5;
    person.set_pname(pname);
    std::cout << "at start" << std::endl;
    person.set_plon(138.5);
    person.set_plat(35.7);
    std::cout << "before output" << std::endl;
    std::cout << "pname: " << person.pname() << std::endl;
    return 0;
}

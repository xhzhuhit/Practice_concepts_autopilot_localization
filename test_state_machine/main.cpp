#include <iostream>


enum STATUS {
    INIT = 0,
    DO_A = 1,
    DO_B = 2,
    DO_C = 3,
    DO_D = 4,
    EXIT = 5
};

STATUS do_preprocess() {
    std::cout << "ganle chushihua !" << std::endl;
    return DO_A;
}

STATUS do_athing() {
    std::cout << "aaaaa !" << std::endl;
    return DO_C;
}
STATUS do_bthing() {
    std::cout << "bbbbb !" << std::endl;
    return DO_D;
}
STATUS do_cthing() {
    std::cout << "ccccc !" << std::endl;
    return EXIT;
}
STATUS do_dthing() {
    std::cout << "ddddd !" << std::endl;
    return EXIT;
}
int main() {
    STATUS _status = INIT;
    for (size_t i = 0; i < 20; ++i) {
    switch (_status) {
        case INIT:
            _status = do_preprocess();
            std::cout << _status << std::endl;
            break;
        case DO_A:
            _status = do_athing();
            break;
        case DO_B:
            _status = do_bthing();
            break;
        case DO_C:
            _status = do_cthing();
            break;
        case DO_D:
            _status = do_dthing();
            break;
        default:
            break;
    }
    }
    return 0;
}

#include <iostream>
#include "Compiler.h"

int main() {
    char path[50];
    std::cout << "please input file path :" << std::endl;
    std::cin >> path;
    Compiler *c = new Compiler(path);
    c->begin();
    return 0;
}
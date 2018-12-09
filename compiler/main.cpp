#include <iostream>
#include "Compiler.h"

int main() {
    //char path[] = "/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/16061075_test.txt";
    char path[50];
    std::cout << "please input file path :" << std::endl;
    std::cin >> path;
    Compiler *c = new Compiler(path);
    c->begin();
    return 0;
}
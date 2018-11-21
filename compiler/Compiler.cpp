//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include <iostream>
#include "Compiler.h"

Compiler::Compiler(char *path) {
    this->infile = std::ifstream(path, std::ios::in);
    if (!this->infile) std::cout << "Wrong File!" << std::endl;
    this->lexerOutFile = std::ofstream("lexer.txt", std::ios::out);
    this->line = 0;
    this->lineLength = 0;
    this->current = 0;
    this->count = 1;

    this->errorList = std::vector<error *>();

    this->index = 0;
    this->top = 0;
    this->address = 0;
    this->funcNum = 0;
    for (int i = 0; i < MAXHASH; i++) this->symbolHash[i] = -1;
}

void Compiler::begin() {
    this->analyze();
}
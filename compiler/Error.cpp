//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include <iostream>
#include "Error.h"
#include "Compiler.h"

void Compiler::errorHandle(int id) {
    error *error = new ::error();
    error->id = id;
    error->token = new std::string(this->token);
    error->line = this->line;
    this->errorList.push_back(error);
    std::cout << "line " << this->line << ":" << this->token << " have " << errorMessage[id] << std::endl;

}

bool Compiler::isInTarget(const int target[], const int size) {
    for (int i = 0; i < size; i++) {
        if (target[i] == this->sym) return true;
    }
    return false;
}

void Compiler::skip(int id) {
    while (this->sym != id && !this->isEOF()) this->getSym();
}

void Compiler::skip(const int target[], const int size) {
    while (!this->isInTarget(target, size) && !this->isEOF()) this->getSym();
}

void Compiler::printError() {
    for (int i = 0; i < this->errorList.size(); i++) {
        error *err = errorList[i];
        this->errorOutFile << "line " << err->line << ":" << *err->token << " have " << errorMessage[err->id]
                           << std::endl;
    }
}
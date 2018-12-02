//
// Created by JJJJJJJiyun on 2018/11/25.
//

#include "MidCode.h"
#include "Compiler.h"

void Compiler::pushMidCode(int op, std::string *op1, std::string *op2, std::string *res) {
    midCode *code = new midCode();
    code->op = op;
    code->op1 = new std::string();
    *code->op1 = *op1;
    code->op2 = new std::string();
    *code->op2 = *op2;
    code->res = new std::string();
    *code->res = *res;
    this->midCodes[this->midCodeIndex++] = code;
}

void Compiler::switchMidCode(int op) {
    int i = this->midCodeIndex - 1;
    while (this->midCodes[i]->op != 0) {
        i--;
    }
    midCode *temp = this->midCodes[i];
    for (; i < this->midCodeIndex; i++) {
        this->midCodes[i] = this->midCodes[i + 1];
    }
    temp->op = op;
    this->midCodes[i - 1] = temp;
}

void Compiler::outputMid() {
    for (int i = 0; i < this->midCodeIndex; i++) {
        midCode *code = this->midCodes[i];
        this->midOutFile << this->midMessage[code->op] << " " << *code->op1 << " " << *code->op2 << " " << *code->res
                         << std::endl;
    }
}



//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include <iostream>
#include "Compiler.h"

Compiler::Compiler(char *path) {
    /*----------词法分析初始化----------*/
    this->infile = std::ifstream(path, std::ios::in);
    if (!this->infile) std::cout << "Wrong File!" << std::endl;
    this->lexerOutFile = std::ofstream("lexer.txt", std::ios::out);
    this->line = 0;
    this->lineLength = 0;
    this->current = 0;
    this->count = 1;

    /*----------语法分析初始化----------*/
    this->mainFlag = false;
    this->syntaxOutFile = std::ofstream("syntax.txt", std::ios::out);

    /*----------错误处理初始化----------*/
    this->errorOutFile = std::ofstream("error.txt", std::ios::out);
    this->errorList = std::vector<error *>();
    this->errorMessage[40] = "single quota error";
    this->errorMessage[41] = "double quota error";
    this->errorMessage[42] = "char error";
    this->errorMessage[43] = "exclamatory mark error";
    this->errorMessage[44] = "illegal terminal error";
    this->errorMessage[45] = "leading zero in num error";
    this->errorMessage[46] = "leading num in id error";
    this->errorMessage[50] = "unsigned int missing error";
    this->errorMessage[51] = "assign missing error";
    this->errorMessage[52] = "int missing error";
    this->errorMessage[53] = "id missing error";
    this->errorMessage[54] = "char missing error";
    this->errorMessage[55] = "int or char missing error";
    this->errorMessage[56] = "semicolon missing error";
    this->errorMessage[57] = "right bracket missing error";
    this->errorMessage[58] = "right parent missing error";
    this->errorMessage[59] = "factor missing error";
    this->errorMessage[60] = "left brace missing error";
    this->errorMessage[61] = "right brace missing error";
    this->errorMessage[62] = "main function missing error";
    this->errorMessage[63] = "left parent missing error";
    this->errorMessage[64] = "statement missing error";
    this->errorMessage[65] = "variable definition missing error";
    this->errorMessage[66] = "unknown function type error";
    this->errorMessage[70] = "duplicated definition error";
    this->errorMessage[71] = "parameter type error";
    this->errorMessage[72] = "parameter number error";
    this->errorMessage[73] = "id not defined";
    this->errorMessage[74] = "not an int expression";
    this->errorMessage[75] = "not an array type id";
    this->errorMessage[76] = "index out of array error";
    this->errorMessage[77] = "not a function type id";
    this->errorMessage[78] = "not a no parameter function";
    this->errorMessage[79] = "invalid id";
    this->errorMessage[80] = "not an int or char id";
    this->errorMessage[81] = "return missing error";
    this->errorMessage[82] = "extra return error";
    this->errorMessage[83] = "return type error";
    this->errorMessage[84] = "illegal assign error";
    this->errorMessage[85] = "not a return function";
    this->errorMessage[86] = "divide zero error";
    this->errorMessage[87] = "while missing error";

    /*----------符号表初始化----------*/
    this->index = 0;
    this->top = 0;
    this->address = 0;
    this->funcNum = 0;
    for (int i = 0; i < MAXHASH; i++) this->symbolHash[i] = -1;
}

void Compiler::begin() {
    this->analyze();
    this->printError();
}
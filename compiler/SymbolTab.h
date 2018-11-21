//
// Created by JJJJJJJiyun on 2018/11/20.
//

#pragma once


#include <string>

#define MAXPARANUM 20
#define MAXBLOCK 2000


typedef struct {
    std::string *name;
    int returnType;
    int symbolType;
    int feature;
    int ref;
    int line;
    int link;
    int paraList[MAXPARANUM];
    int address;
    bool flag[MAXBLOCK];
    int reg;
} symbol;

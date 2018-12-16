//
// Created by JJJJJJJiyun on 2018/12/12.
//
#pragma once

#include <string>

const int MAXNODE = 100;

typedef struct {
    int preArray[400];
    int preNum;
    int next1;
    int next2;
} Block;

typedef struct {
    int edgeNum;
    bool connect[1000];
} ConflictNode;

typedef struct {
    std::string *name;
    int index;
} ListNode;

typedef struct {
    int op;
    std::string *name;
    int xIndex;
    int yIndex;
    int parentIndex[30];
    int parentNum;
    int index;
    bool flag;
    bool isLeaf;
} Node;




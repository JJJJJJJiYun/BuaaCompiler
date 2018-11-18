//
// Created by JJJJJJJiyun on 2018/11/12.
//

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "definition.h"

using namespace std;
class Lexer {
public:
    static char ch;
    static string path, inputLine, token;
    static int sym, line, lineLength, current, count1, count2;
    static ifstream infile;
    static ofstream outfile;
    static void getSym();
    static void output();
    static void outputToFile();
    static void init();
    static void run();
    static void close();
private:
    static void freshToken();
    static void getNextLine();
    static void getChar();
    static void skip();
    static bool isLetter();
    static bool isDigit();
    static void constructToken();
    static int isReserve();
    static bool isLegalString();
};

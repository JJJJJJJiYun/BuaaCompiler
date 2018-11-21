//
// Created by JJJJJJJiyun on 2018/11/20.
//
#pragma once

#include <fstream>
#include <vector>
#include "Error.h"
#include "SymbolTab.h"

#define MAXSYMBOL 5000
#define MAXHASH 4096
#define MAXSTRINGNUM 1000
#define MAXFUNCNUM 500
#define MAXFUNCSYMBOL 1000


class Compiler {
public:
    Compiler(char *path); //构造器
    void begin(); //开始编译

private:
    /*----------词法分析----------*/
    std::ifstream infile; //读入的文件
    std::ofstream lexerOutFile;
    char ch; //当前字符
    std::string inputLine, token; //输入的语句 当前token
    int sym, line, lineLength, current, count; //当前sym 当前行数 当前行长度 当前字符下标 当前计数
    void getSym(); //获取sym
    void freshToken(); //刷新token
    void getNextLine(); //获取下一行
    void getChar(); //获取当前字符
    void skip(); //跳读
    bool isLetter(); //是否为字母
    bool isDigit(); //是否为数字
    void constructToken(); //将字符加入token
    int isReserve(); //判断是否为保留字
    bool isLegalString(); //判断是否为合法字符串
    void output();

    bool isEOF();

    /*----------语法分析----------*/
    int temp;
    int label;

    void analyze();

    void constState();

    void constDef();

    void constructInt(int *value);

    void afterConst();

    void getReturnType(int *returnType, std::string **name);

    void genTemp(std::string *temp);

    void genLabel(std::string *label);

    void varDef(int returnType, std::string *name);

    void paraFuncDef(symbol *sym);

    void paraProcess(symbol *sym);

    void noParaFuncDef(symbol *sym);

    void compoundProcess(bool *flag, int returnType, std::string *name);

    void varState();

    void statementsProcess(bool *flag, int returnType, std::string *name);

    void statementProcess(bool *flag, int returnType, std::string *funcName);

    void ifProcess(bool *flag, int returnType, std::string *name);

    void conditionProcess(std::string *label);

    void expressionProcess(int *resultType, std::string *operand);

    void termProcess(int *resultType, std::string *operand);

    void factorProcess(int *resultType, std::string *operand);

    bool isOperandNum(std::string *s);

    void paraListProcess(symbol *sym);

    void int2String(std::string *s, int value);

    void constProcess(int *value, int *returnType);

    bool isOperandReturn(std::string *s);

    bool isOperandTemp(std::string *s);

    bool isOperandId(std::string *s);

    void scanfProcess();

    void printfProcess();

    void returnProcess(bool *flag, int returnType, std::string *name);

    void doWhileProcess(bool *flag, int returnType, std::string *name);

    void forProcess(bool *flag, int returnType, std::string *name);

    void reassignProcess(bool *flag, int returnType, std::string *name);

    void afterVar();

    void voidFuncDef();

    void mainDef();


    /*----------错误处理----------*/
    std::vector<error *> errorList;

    void errorHandle(int id);

    void skip(int id);

    void skip(const int target[], const int size);

    bool isInTarget(const int target[], const int size);

    void printError();

    /*----------符号表----------*/
    symbol *symbolTab[MAXSYMBOL];
    int symbolHash[MAXHASH];
    int index;
    int top;
    int address;
    int stringNum;
    std::string *stringTab[MAXSTRINGNUM];
    int funcSymbolNum[MAXFUNCNUM];
    int funcMaxAddress[MAXFUNCNUM];
    int globalAddress;
    int funcNum;
    symbol **funcSymbolTab[MAXFUNCSYMBOL];

    unsigned int hash(const char *str);

    bool isEqual(std::string id1, std::string id2);

    bool find(std::string *name, symbol **sym, bool local);

    symbol *push(std::string *name, int returnType, int symbolType, int feature, int line);

    void prepareFunc();

    void pushString(std::string *str, int *index);

    void pop();

};

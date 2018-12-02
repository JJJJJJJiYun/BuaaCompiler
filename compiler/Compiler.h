//
// Created by JJJJJJJiyun on 2018/11/20.
//
#pragma once

#include <fstream>
#include <vector>
#include <map>
#include "Error.h"
#include "SymbolTab.h"
#include "MidCode.h"

#define MAXSYMBOL 5000
#define MAXHASH 4096
#define MAXSTRINGNUM 1000
#define MAXFUNCNUM 500
#define MAXFUNCSYMBOL 1000
#define MAXMIDCODE 5000
#define MAXMIPSCODE 10000
#define MAXREG 14


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

    void output(); //输出词法分析结果

    bool isEOF(); //文件是否结束

    void breakProcess(); //处理\n

    /*----------语法分析----------*/
    int temp; //临时变量
    int label; //标签
    bool mainFlag;
    std::ofstream syntaxOutFile;

    void analyze(); //语法分析

    void constState(); //常量声明

    void constDef(); //常量定义

    void constructInt(int *value); //构造数字

    void afterConst(); //处理常量声明之后的语句

    void getReturnType(int *returnType, std::string **name); //获取返回值类型

    void genTemp(std::string *temp);  //生成临时变量

    void genLabel(std::string *label); //生成标签

    void varState(); //变量声明

    void varDef(int returnType, std::string *name); //变量定义

    void paraFuncDef(symbol *sym); //有参函数定义

    void paraProcess(symbol *sym); //参数处理

    void noParaFuncDef(symbol *sym); //无参函数处理

    void compoundProcess(bool *flag, int returnType, std::string *name); //复合语句处理

    void statementsProcess(bool *flag, int returnType, std::string *name); //语句列处理

    void statementProcess(bool *flag, int returnType, std::string *funcName); //语句处理

    void ifProcess(bool *flag, int returnType, std::string *name); //if语句处理

    void conditionProcess(std::string *label); //条件语句处理

    void expressionProcess(int *resultType, std::string *operand); //表达式处理

    void termProcess(int *resultType, std::string *operand); //项处理

    void factorProcess(int *resultType, std::string *operand); //因子处理

    bool isOperandNum(std::string *s); //操作数是否为数字

    void paraListProcess(symbol *sym); //参数列处理

    void int2String(std::string *s, int value); //数字转字符串

    void constProcess(int *value, int *returnType); //常量处理

    bool isOperandReturn(std::string *s); //操作数是否为返回值

    bool isOperandTemp(std::string *s); //操作数是否为临时变量

    bool isOperandId(std::string *s); //操作数是否为标识符

    void scanfProcess(); //读入语句处理

    void printfProcess(); //输出语句处理

    void returnProcess(bool *flag, int returnType, std::string *name); //返回语句处理

    void doWhileProcess(bool *flag, int returnType, std::string *name); //do_while处理

    void forProcess(bool *flag, int returnType, std::string *name); //for处理

    void assignOrFuncProcess(bool *flag, int returnType, std::string *name); //变量赋值处理

    void afterVar(); //处理变量声明之后的语句

    void voidFuncDef(); //无返回值函数定义

    void mainDef(); //main函数定义

    void forAssignProcess(bool *flag, int returnType, std::string *name, bool first);


    /*----------错误处理----------*/
    std::vector<error *> errorList; //错误列表
    std::map<int, std::string> errorMessage; //错误信息图
    std::ofstream errorOutFile;

    void errorHandle(int id); //错误处理

    void skip(int id); //跳过到某个符号

    void skip(const int target[], const int size); //跳过到某些符号

    bool isInTarget(const int target[], const int size); //是否在某些符号中

    void printError(); //打印错误

    /*----------符号表----------*/
    symbol *symbolTab[MAXSYMBOL]; //符号表
    int symbolHash[MAXHASH]; //符号哈希表
    int index; //下标
    int top; //最大下标
    int address; //地址
    int stringNum; //字符串数
    std::string *stringTab[MAXSTRINGNUM]; //字符串表
    int funcSymbolNum[MAXFUNCNUM]; //函数符号数表
    int funcMaxAddress[MAXFUNCNUM]; //函数地址表
    int globalAddress; //全局地址
    int funcNum; //函数数
    symbol **funcSymbolTab[MAXFUNCSYMBOL]; //函数符号表

    unsigned int hash(const char *str); //哈希

    bool isEqual(std::string id1, std::string id2); //判断是否相同

    bool find(std::string *name, symbol **sym, bool local); //符号是否在表中

    symbol *push(std::string *name, int returnType, int symbolType, int feature, int line); //加入符号表

    void prepareFunc(); //函数定义准备

    void pushString(std::string *str, int *index); //加入字符串

    void pop(); //推出

    /*----------中间代码----------*/
    midCode *midCodes[MAXMIDCODE];
    int midCodeIndex;
    std::ofstream midOutFile;
    std::map<int, std::string> midMessage;

    void pushMidCode(int op, std::string *op1, std::string *op2, std::string *res);

    void switchMidCode(int op);

    void outputMid();

    /*----------目标代码----------*/
    std::string *mipsCodes[MAXMIPSCODE];
    std::ofstream mipsOutFile;
    int mipsIndex;
    int currentRef;
    std::string *regs[MAXREG];

    void generate();

    void initAscii();

    void generateCode(std::string *code);

    void pushCode(std::string *code);

    void outputMips();

    void generateCode(std::string *code, std::string *rd, std::string *rs, std::string *rt);

    void generateCode(std::string *code, std::string *rd, std::string *rt, int immediate);

    void generateCode(std::string *code, std::string *target);

    void generateCode(std::string *code, std::string *rs, int num, std::string *rt);

    void generateCode(std::string *code, std::string *rs, std::string *label);

    void generateCode(std::string *code, std::string *rs, int num);

    void gotoProcess(std::string *label);

    void funcProcess(std::string *name);

    void branchProcess(midCode *code);

    void paraProcess(std::string *para);

    void rArrayProcess(midCode *code);

    void lArrayProcess(midCode *code);

    void callProcess(std::string *name);

    void returnProcess(std::string *name);

    void multiProcess(midCode *code);

    void addProcess(midCode *code);

    void subProcess(midCode *code);

    void scanfProcess(midCode *code);

    void printfProcess(midCode *code);

    void exitProcess();

    void genMipsLabel(std::string *label);

    void str2Lower(std::string *oldStr, std::string *newStr);

    void getUseReg(std::string *rs, std::string *reg);

    void getResultReg(std::string *rd, std::string *reg);

    void findSym(std::string *name, symbol **resultSym, bool *flag);

    void writeBack(std::string *rd, std::string *reg);

};

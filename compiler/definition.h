//
// Created by JJJJJJJiyun on 2018/11/20.
//

#pragma once

#include <string>
//default
#define NONE      0  // default

//符号
#define PLUS      1  // +
#define MINUS     2  // -
#define MULTI      3  // *
#define DIVIDE       4  // /
#define LESS      5  // <
#define LESSEQU   6  // <=
#define GREATEQU  7  // >=
#define GREAT     8  // >
#define NEQUAL    9  // !=
#define EQUAL     10 // ==
#define ASSIGN    11 // =
#define LPARENT   12 // (
#define RPARENT   13 // )
#define LBRACK    14 // [
#define RBRACK    15 // ]
#define LBRACE    16 // {
#define RBRACE    17 // }
#define COMMA     18 // ,
#define SEMICOLON 19 // ;

//数据及其类型
#define ID        20 // id
#define UNSIGNEDINT 21 // unsigned int
#define ZERO      22 // zero
#define CHAR      23 // character
#define STRING    24 // string

//保留字
#define MAINSYM   25 // main
#define INTSYM    26 // int
#define CHARSYM   27 // char
#define CONSTSYM  28 // const
#define VOIDSYM   29 // void
#define IFSYM     30 // if
#define ELSESYM   31 // else
#define DOSYM     32 // do
#define WHILESYM  33 // while
#define FORSYM    34 // for
#define SCANFSYM  35 // scanf
#define PRINTFSYM 36 // printf
#define RETURNSYM 37 // return

//词法分析错误
#define SQERROR 40
#define DQERROR 41
#define CHARERROR 42
#define EMERROR 43
#define TERMINALERROR 44
#define FORMERZEROERROR 45
#define FORMERNUMERROR 46

//语法分析错误
#define UNSIGNEDINTERROR 50
#define ASSIGNERROR 51
#define INTERROR 52
#define IDERROR 53
#define SINGLECHARERROR 54
#define INTORCHARERROR 55
#define SEMICOLONERROR 56
#define RBRACKERROR 57
#define RPARENTERROR 58
#define FACTORERROR 59
#define LBRACEERROR 60
#define RBRACEERROR 61
#define MAINERROR 62
#define LPARENTERROR 63
#define STATEMENTERROR 64
#define VARDEFERROR 65
#define UNKNOWNERROR 66

//语义、符号表错误
#define DUPLICATEERROR 70
#define PARATYPEERROR 71
#define PARANUMERROR 72
#define IDDEFINEERROR 73
#define INTEXPERROR 74
#define ARRAYERROR 75
#define ARRAYOUTERROR 76
#define FUNCERROR 77
#define NOPARAFUNCERROR 78
#define IDUSEERROR 79
#define SIMPLEVARERROR 80
#define RETURNMISSERROR 81
#define RETURNEXTRAERROR 82
#define RETURNERROR 83
#define ILLEGALASSERROR 84
#define RETURNFUNCERROR 85
#define ZEROERROR 86
#define NOWHILEERROR 87

#define SIMPLESYM 90
#define ARRAYSYM 91
#define FUNCSYM 92
#define PARASYM 93

#define PARA 100
#define CALL 101
#define RET 102
#define LARRAY 103
#define RARRAY 104
#define ADD 105
#define SUB 106
#define MUL 107
#define DIV 108
#define EQU 109
#define NEQU 110
#define GRE 111
#define GREEQU 112
#define LE 113
#define LEEQU 114
#define LABEL 115
#define GOTO 116
#define FUNC 117
#define SCAN 118
#define PRINT 119
#define EXIT 120

//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "Syntax.h"

const int INT[] = {PLUS, MINUS, UNSIGNEDINT, ZERO};
const int INT_SIZE = 4;
const int NUM[] = {LESSEQU, GREATEQU, EQUAL, NEQUAL, LESS, GREAT, PLUS, MINUS, MULTI, DIVIDE, COMMA, SEMICOLON,
                   RBRACK, RPARENT};
const int NUM_SIZE = 14;
const int END[] = {SEMICOLON, COMMA};
const int END_SIZE = 2;
const int VARDEF[] = {LBRACK, COMMA, SEMICOLON};
const int VARDEF_SIZE = 3;
const int DEF[] = {INTSYM, CHARSYM};
const int DEF_SIZE = 2;
const int STATEMENT[] = {IFSYM, DOSYM, WHILESYM, FORSYM, PRINTFSYM, SCANFSYM, RETURNSYM, LBRACE, SEMICOLON, ID};
const int STATEMENT_SIZE = 10;
const int FACTOR[] = {PLUS, MINUS, MULTI, DIVIDE, SEMICOLON, COMMA, RPARENT, RBRACK};
const int FACTOR_SIZE = 8;
const int CONST[] = {CHAR, PLUS, MINUS, UNSIGNEDINT, ZERO};
const int CONST_SIZE = 5;
const int RELATION[] = {LESSEQU, GREATEQU, EQUAL, NEQUAL, LESS, GREAT};
const int RELATION_SIZE = 6;

std::string *ZEROOP = new std::string("0");


void Compiler::constructInt(int *value) {
    bool flag = false;
    int result = 0;
    if (this->sym == 0) {
        this->errorHandle(UNSIGNEDINTERROR);
        this->skip(NUM, NUM_SIZE);
    } else {
        if (this->sym == PLUS || this->sym == MINUS) {
            flag = this->sym == MINUS;
            this->getSym();
            if (this->sym == UNSIGNEDINT) {
                result = atoi(this->token.c_str());
                this->getSym();
            } else {
                this->errorHandle(UNSIGNEDINTERROR);
                this->skip(NUM, NUM_SIZE);
            }
        } else {
            result = atoi(this->token.c_str());
            this->getSym();
        }
    }
    *value = flag ? -result : result;
}

void Compiler::constDef() {
    this->syntaxOutFile << "const def" << std::endl;
    int symbolType = CONSTSYM;
    if (this->sym == INTSYM) {
        int returnType = INTSYM;
        do {
            this->syntaxOutFile << "num const" << std::endl;
            int value = 0;
            std::string *name = 0;
            this->getSym();
            if (this->sym == ID) {
                name = new std::string(this->token);
                this->getSym();
                if (this->sym == ASSIGN) {
                    this->getSym();
                    if (this->isInTarget(INT, INT_SIZE)) {
                        this->constructInt(&value);
                        symbol *sym = 0;
                        if (!this->find(name, &sym, true))
                            this->push(name, returnType, symbolType, value, this->line);
                        else
                            this->errorHandle(DUPLICATEERROR);
                    } else {
                        this->errorHandle(INTERROR);
                        this->skip(END, END_SIZE);
                    }
                } else {
                    this->errorHandle(ASSIGNERROR);
                    this->skip(END, END_SIZE);
                }
            } else {
                this->errorHandle(IDERROR);
                this->skip(END, END_SIZE);
            }
        } while (this->sym == COMMA);
    } else if (this->sym == CHARSYM) {
        int returnType = CHARSYM;
        do {
            this->syntaxOutFile << "char const" << std::endl;
            int value = 0;
            std::string *name = 0;
            this->getSym();
            if (this->sym == ID) {
                name = new std::string(this->token);
                this->getSym();
                if (this->sym == ASSIGN) {
                    this->getSym();
                    if (this->sym == CHAR) {
                        value = this->token[0];
                        symbol *sym = 0;
                        if (!this->find(name, &sym, true))
                            this->push(name, returnType, symbolType, value, this->line);
                        else
                            this->errorHandle(DUPLICATEERROR);
                        this->getSym();
                    } else {
                        this->errorHandle(SINGLECHARERROR);
                        this->skip(END, END_SIZE);
                    }
                } else {
                    this->errorHandle(SINGLECHARERROR);
                    this->skip(END, END_SIZE);
                }
            } else {
                this->errorHandle(IDERROR);
                this->skip(END, END_SIZE);
            }
        } while (this->sym == COMMA);
    } else {
        this->errorHandle(INTORCHARERROR);
        this->skip(SEMICOLON);
    }
    this->syntaxOutFile << "const def end" << std::endl;
}

void Compiler::constState() {
    do {
        this->getSym();
        this->constDef();
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
    } while (this->sym == CONSTSYM);
}

void Compiler::getReturnType(int *returnType, std::string **name) {
    if (this->sym == INTSYM || this->sym == CHARSYM)
        *returnType = this->sym;
    else
        this->errorHandle(INTORCHARERROR);
    this->getSym();
    if (this->sym == ID) {
        *name = new std::string(this->token);
        this->getSym();
    } else {
        this->errorHandle(IDERROR);
        this->getSym();
    }
}

void Compiler::genTemp(std::string *temp) {
    std::stringstream stringStream = std::stringstream();
    stringStream << "$t";
    stringStream << this->temp++;
    *temp = stringStream.str();
    this->push(temp, INTSYM, SIMPLESYM, -1, this->line);
}

void Compiler::varDef(int returnType, std::string *name) {
    this->syntaxOutFile << "var def" << std::endl;
    symbol *sym = 0;
    if (this->find(name, &sym, true))
        this->errorHandle(DUPLICATEERROR);
    if (this->sym == SEMICOLON) {
        this->push(name, returnType, SIMPLESYM, -1, this->line);
        this->getSym();
        this->syntaxOutFile << "var" << std::endl;
        this->syntaxOutFile << "var def end" << std::endl;
        return;
    }
    if (this->sym == LBRACK) {
        this->syntaxOutFile << "var" << std::endl;
        int feature = -1;
        this->getSym();
        if (this->sym == UNSIGNEDINT) {
            feature = atoi(this->token.c_str());
            this->getSym();
        } else
            this->errorHandle(UNSIGNEDINTERROR);
        if (this->sym == RBRACK) {
            this->push(name, returnType, ARRAYSYM, feature, this->line);
            this->getSym();
        } else
            this->errorHandle(RBRACKERROR);
    } else {
        this->syntaxOutFile << "var" << std::endl;
        this->push(name, returnType, SIMPLESYM, -1, this->line);
    }

    while (this->sym == COMMA) {
        this->syntaxOutFile << "var" << std::endl;
        std::string *name2 = 0;
        this->getSym();
        if (this->sym == ID) {
            symbol *sym = 0;
            if (this->find(new std::string(this->token), &sym, true))
                this->errorHandle(DUPLICATEERROR);
            name2 = new std::string(this->token);
            this->getSym();
        } else
            this->errorHandle(IDERROR);
        int feature = -1;
        if (this->sym == LBRACK) {
            this->getSym();
            if (this->sym == UNSIGNEDINT) {
                feature = atoi(this->token.c_str());
                this->getSym();
            } else
                this->errorHandle(UNSIGNEDINTERROR);
            if (this->sym == RBRACK) {
                this->push(name2, returnType, ARRAYSYM, feature, this->line);
                this->getSym();
            } else
                this->errorHandle(RBRACKERROR);
        } else {
            this->push(name2, returnType, SIMPLESYM, -1, this->line);
        }
    }
    this->syntaxOutFile << "var def end" << std::endl;
    if (this->sym == SEMICOLON)
        this->getSym();
    else
        this->errorHandle(SEMICOLONERROR);
}

void Compiler::paraProcess(symbol *sym) {
    this->syntaxOutFile << "para process" << std::endl;
    std::string *name = 0;
    int returnType = NONE;
    this->getReturnType(&returnType, &name);
    if (!name) {
        name = new std::string();
        this->genTemp(name);
    }
    this->syntaxOutFile << "para" << std::endl;
    sym->paraList[sym->feature++] = returnType;
    symbol *temp = 0;
    if (this->find(name, &temp, true)) {
        this->errorHandle(DUPLICATEERROR);
        return;
    } else
        this->push(name, returnType, PARASYM, -1, this->line);
    while (this->sym == COMMA) {
        this->syntaxOutFile << "para" << std::endl;
        std::string *name = 0;
        int returnType = NONE;
        this->getSym();
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        sym->paraList[sym->feature++] = returnType;
        symbol *temp = 0;
        if (this->find(name, &temp, true)) {
            this->errorHandle(DUPLICATEERROR);
            return;
        } else
            this->push(name, returnType, PARASYM, -1, this->line);
    }
    this->syntaxOutFile << "para process end" << std::endl;
}

void Compiler::varState() {
    int returnType = NONE;
    std::string *name = 0;
    this->getReturnType(&returnType, &name);
    if (!name) {
        name = new std::string();
        this->genTemp(name);
    }
    if (this->isInTarget(VARDEF, VARDEF_SIZE))
        this->varDef(returnType, name);
    else {
        this->errorHandle(VARDEFERROR);
        this->skip(DEF, DEF_SIZE);
        return;
    }
    while (this->isInTarget(DEF, DEF_SIZE)) {
        int returnType = NONE;
        std::string *name = 0;
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        if (this->isInTarget(VARDEF, VARDEF_SIZE))
            this->varDef(returnType, name);
        else {
            this->errorHandle(VARDEFERROR);
            this->skip(DEF, DEF_SIZE);
            return;
        }
    }
}

bool Compiler::isOperandNum(std::string *s) {
    return s->length() > 0 ? (*s)[0] >= '0' && (*s)[0] <= '9' || (*s)[0] == '-' : false;
}

void Compiler::paraListProcess(symbol *sym) {
    int type = NONE;
    int index = 0;
    std::string para = std::string();
    this->expressionProcess(&type, &para);
    this->pushMidCode(PARA, &para, ZEROOP, &para);
    if (sym->feature > index) {
        if (sym->paraList[index] != type)
            this->errorHandle(PARATYPEERROR);
    } else {
        this->errorHandle(PARANUMERROR);
        this->skip(RPARENT);
        return;;
    }
    index++;
    while (this->sym == COMMA) {
        int type = NONE;
        this->getSym();
        std::string para = std::string();
        this->expressionProcess(&type, &para);
        this->pushMidCode(PARA, &para, ZEROOP, &para);
        if (sym->feature > index) {
            if (sym->paraList[index] != type)
                this->errorHandle(PARATYPEERROR);
        } else {
            this->errorHandle(PARANUMERROR);
            this->skip(RPARENT);
            return;;
        }
        index++;
    }
    if (index != sym->feature) {
        this->errorHandle(PARANUMERROR);
        this->skip(RPARENT);
        return;
    }
}

void Compiler::int2String(std::string *s, int value) {
    std::stringstream ss = std::stringstream();
    ss << value;
    *s = ss.str();
}

void Compiler::constProcess(int *value, int *returnType) {
    if (this->sym == CHAR) {
        *returnType = CHARSYM;
        *value = this->token[0];
        this->getSym();
    } else {
        *returnType = INTSYM;
        this->constructInt(value);
    }
}

void Compiler::factorProcess(int *resultType, std::string *operand) {
    if (this->sym == ID) {
        symbol *sym = 0;
        if (!this->find(new std::string(this->token), &sym, false)) {
            this->errorHandle(IDDEFINEERROR);
            this->skip(FACTOR, FACTOR_SIZE);
            return;
        }
        *resultType = sym->returnType;
        this->getSym();
        //数组
        if (this->sym == LBRACK) {
            if (sym->symbolType != ARRAYSYM)
                this->errorHandle(ARRAYERROR);
            int type = NONE;
            this->getSym();
            std::string temp = std::string();
            this->expressionProcess(&type, &temp);
            if (type != INTSYM)
                this->errorHandle(INTEXPERROR);
            if (this->isOperandNum(&temp)) {
                int constValue = atoi(temp.c_str());
                if (constValue >= sym->feature || constValue < 0)
                    this->errorHandle(ARRAYOUTERROR);
            }
            this->genTemp(operand);
            this->pushMidCode(RARRAY, sym->name, &temp, operand);
            if (this->sym == RBRACK)
                this->getSym();
            else
                this->errorHandle(RBRACKERROR);
        }
            //函数调用
        else if (this->sym == LPARENT) {
            if (sym->symbolType != FUNCSYM) {
                this->errorHandle(FUNCERROR);
                return;;
            }
            if (sym->returnType == VOIDSYM)
                this->errorHandle(RETURNFUNCERROR);
            this->getSym();
            if (this->sym != RPARENT)
                this->paraListProcess(sym);
            if (this->sym == RPARENT) {
                this->pushMidCode(CALL, new std::string(), new std::string(), sym->name);
                *operand = std::string("#RET");
                this->getSym();
            } else
                this->errorHandle(RPARENTERROR);
        }
            //变量
        else {
            if (sym->symbolType == SIMPLESYM || sym->symbolType == PARASYM)
                *operand = *sym->name;
            else if (sym->symbolType == FUNCSYM) {
                if (sym->feature != 0)
                    this->errorHandle(NOPARAFUNCERROR);
                this->pushMidCode(CALL, new std::string(), new std::string(), sym->name);
                *operand = std::string("#RET");
            } else if (sym->symbolType == CONSTSYM) {
                int value = sym->feature;
                std::string constValue = std::string();
                this->int2String(&constValue, value);
                *operand = constValue;
            } else
                this->errorHandle(IDUSEERROR);
        }
    } else if (this->sym == LPARENT) {
        this->getSym();
        this->expressionProcess(resultType, operand);
        if (this->sym == RPARENT)
            this->getSym();
        else
            this->errorHandle(RPARENTERROR);
    } else if (this->isInTarget(CONST, CONST_SIZE)) {
        int value;
        this->constProcess(&value, resultType);
        std::string constValue = std::string();
        this->int2String(&constValue, value);
        *operand = constValue;
    } else {
        this->errorHandle(FACTORERROR);
        this->skip(FACTOR, FACTOR_SIZE);
    }
}

bool Compiler::isOperandReturn(std::string *s) {
    return s->length() > 0 ? (*s)[0] == '#' : false;
}

bool Compiler::isOperandTemp(std::string *s) {
    return s->length() > 0 ? (*s)[0] == '$' : false;
}

void Compiler::termProcess(int *resultType, std::string *operand) {
    std::string operand1 = std::string();
    this->factorProcess(resultType, &operand1);
    if (this->isOperandReturn(&operand1)) {
        std::string temp = std::string();
        this->genTemp(&temp);
        this->pushMidCode(ADD, &operand1, ZEROOP, &temp);
        operand1 = temp;
    }
    while (this->sym == MULTI || this->sym == DIVIDE) {
        *resultType = INTSYM;
        bool flag = this->sym == MULTI;
        int fact = NONE;
        std::string operand2 = std::string();
        this->getSym();
        this->factorProcess(&fact, &operand2);
        if (this->isOperandNum(&operand1)) {
            if (this->isOperandNum(&operand2)) {
                int op1 = atoi(operand1.c_str());
                int op2 = atoi(operand2.c_str());
                if (op2 == 0 && !flag) {
                    this->errorHandle(ZEROERROR);
                    op2 += 1;
                }
                int result = flag ? op1 * op2 : op1 / op2;
                std::string constValue = std::string();
                this->int2String(&constValue, result);
                operand1 = constValue;
            } else {
                if (!this->isOperandTemp(&operand2)) {
                    std::string result = std::string();
                    this->genTemp(&result);
                    this->pushMidCode(flag ? MUL : DIV, &operand1, &operand2, &result);
                    operand1 = result;
                } else {
                    this->pushMidCode(flag ? MUL : DIV, &operand1, &operand2, &operand2);
                    operand1 = operand2;
                }
            }
        } else {
            if (this->isOperandNum(&operand2)) {
                int op2 = atoi(operand2.c_str());
                if (op2 == 0 && !flag)
                    this->errorHandle(ZEROERROR);
            }
            if (this->isOperandTemp(&operand1)) {
                this->pushMidCode(flag ? MUL : DIV, &operand1, &operand2, &operand1);
            } else {
                std::string result = std::string();
                this->genTemp(&result);
                this->pushMidCode(flag ? MUL : DIV, &operand1, &operand2, &result);
                operand1 = result;
            }
        }
    }
    *operand = operand1;
}

bool Compiler::isOperandId(std::string *s) {
    return s->length() > 0 ? (*s)[0] == '-' || ((*s)[0] >= 'A' && (*s)[0] <= 'Z') || ((*s)[0] >= 'a' && (*s)[0] <= 'z')
                           : false;
}

void Compiler::expressionProcess(int *resultType, std::string *operand) {
    std::string operand1 = std::string();
    bool flag1 = false;
    bool flag2 = false;
    if (this->sym == PLUS || this->sym == MINUS) {
        flag1 = true;
        flag2 = this->sym == MINUS;
        this->getSym();
    }
    this->termProcess(resultType, &operand1);
    if (flag2) {
        if (this->isOperandNum(&operand1)) {
            int value = -atoi(operand1.c_str());
            std::string constValue = std::string();
            this->int2String(&constValue, value);
            operand1 = constValue;
        } else if (this->isOperandId(&operand1)) {
            std::string temp = std::string();
            this->genTemp(&temp);
            this->pushMidCode(SUB, ZEROOP, &operand1, &temp);
            operand1 = temp;
        } else
            this->pushMidCode(SUB, ZEROOP, &operand1, &operand1);
    }
    *resultType = flag1 ? INTSYM : *resultType;
    while (this->sym == PLUS || this->sym == MINUS) {
        bool flag3 = this->sym == PLUS;
        int result = NONE;
        std::string operand2 = std::string();
        this->getSym();
        this->termProcess(&result, &operand2);
        *resultType = INTSYM;
        if (this->isOperandNum(&operand1)) {
            if (this->isOperandNum(&operand2)) {
                int op1 = atoi(operand1.c_str());
                int op2 = atoi(operand2.c_str());
                int result = flag3 ? op1 + op2 : op1 - op2;
                std::string constValue = std::string();
                this->int2String(&constValue, result);
                operand1 = constValue;
            } else {
                if (this->isOperandId(&operand2)) {
                    std::string temp = std::string();
                    this->genTemp(&temp);
                    this->pushMidCode(flag3 ? ADD : SUB, &operand1, &operand2, &temp);
                    operand1 = temp;
                } else {
                    this->pushMidCode(flag3 ? ADD : SUB, &operand1, &operand2, &operand2);
                    operand1 = operand2;
                }
            }
        } else {
            if (this->isOperandTemp(&operand1)) {
                this->pushMidCode(flag3 ? ADD : SUB, &operand1, &operand2, &operand1);
            } else {
                std::string temp = std::string();
                this->genTemp(&temp);
                this->pushMidCode(flag3 ? ADD : SUB, &operand1, &operand2, &temp);
                operand1 = temp;
            }
        }
    }
    *operand = operand1;
}

void Compiler::genLabel(std::string *label) {
    std::stringstream stringStream = std::stringstream();
    stringStream << "$label";
    stringStream << this->label++;
    *label = stringStream.str();
}

void Compiler::conditionProcess(std::string *label) {
    this->syntaxOutFile << "condition statement" << std::endl;
    int returnType = NONE;
    std::string operand1 = std::string();
    this->expressionProcess(&returnType, &operand1);
    if (this->isInTarget(RELATION, RELATION_SIZE)) {
        int relation = this->sym;
        int returnType2 = NONE;
        std::string operand2 = std::string();
        this->getSym();
        this->expressionProcess(&returnType2, &operand2);
        switch (relation) {
            case EQUAL:
                this->pushMidCode(NEQU, &operand1, &operand2, label);
                break;
            case NEQUAL:
                this->pushMidCode(EQU, &operand1, &operand2, label);
                break;
            case LESSEQU:
                this->pushMidCode(GRE, &operand1, &operand2, label);
                break;
            case LESS:
                this->pushMidCode(GREEQU, &operand1, &operand2, label);
                break;
            case GREATEQU:
                this->pushMidCode(LE, &operand1, &operand2, label);
                break;
            case GREAT:
                this->pushMidCode(LEEQU, &operand1, &operand2, label);
                break;
        }
    } else
        this->pushMidCode(EQU, &operand1, ZEROOP, label);
}

void Compiler::ifProcess(bool *flag, int returnType, std::string *name) {
    this->syntaxOutFile << "if statement" << std::endl;
    this->getSym();
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    std::string *elseLabel = new std::string();
    this->genLabel(elseLabel);
    std::string *endLabel = new std::string();
    this->genLabel(endLabel);
    this->conditionProcess(elseLabel);
    if (this->sym == RPARENT)
        this->getSym();
    else {
        this->errorHandle(RPARENTERROR);
        this->skip(STATEMENT, STATEMENT_SIZE);
    }
    if (this->isInTarget(STATEMENT, STATEMENT_SIZE))
        this->statementProcess(flag, returnType, name);
    else
        this->errorHandle(STATEMENTERROR);
    this->pushMidCode(GOTO, new std::string(), new std::string(), endLabel);
    this->pushMidCode(LABEL, new std::string(), new std::string(), elseLabel);
    if (this->sym == ELSESYM) {
        this->syntaxOutFile << "else statement" << std::endl;
        this->getSym();
        if (this->isInTarget(STATEMENT, STATEMENT_SIZE))
            this->statementProcess(flag, returnType, name);
        else {
            this->errorHandle(STATEMENTERROR);
            this->skip(STATEMENT, STATEMENT_SIZE);
        }
    }
    this->pushMidCode(LABEL, new std::string(), new std::string(), endLabel);
}

void Compiler::scanfProcess() {
    this->syntaxOutFile << "scanf" << std::endl;
    this->getSym();
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    if (this->sym == ID) {
        symbol *sym = 0;
        if (!this->find(new std::string(this->token), &sym, false)) {
            this->errorHandle(IDDEFINEERROR);
            this->skip(SEMICOLON);
            return;
        }
        if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
            this->errorHandle(SIMPLEVARERROR);
        switch (sym->returnType) {
            case INTSYM:
                this->pushMidCode(SCAN, sym->name, new std::string("int"), sym->name);
                break;
            case CHARSYM:
                this->pushMidCode(SCAN, sym->name, new std::string("char"), sym->name);
                break;
        }
        this->getSym();
    } else {
        this->errorHandle(IDERROR);
        this->skip(END, END_SIZE);
        return;
    }
    while (this->sym == COMMA) {
        this->getSym();
        if (this->sym == ID) {
            symbol *sym = 0;
            if (!this->find(new std::string(this->token), &sym, false)) {
                this->errorHandle(IDDEFINEERROR);
                this->skip(SEMICOLON);
                return;
            }
            if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
                this->errorHandle(SIMPLEVARERROR);
            switch (sym->returnType) {
                case INTSYM:
                    this->pushMidCode(SCAN, sym->name, new std::string("int"), sym->name);
                    break;
                case CHARSYM:
                    this->pushMidCode(SCAN, sym->name, new std::string("char"), sym->name);
                    break;
            }
            this->getSym();
        } else {
            this->errorHandle(IDERROR);
            this->skip(END, END_SIZE);
            continue;
        }
    }
    if (this->sym == RPARENT)
        this->getSym();
    else
        this->errorHandle(RPARENTERROR);
}

void Compiler::printfProcess() {
    this->syntaxOutFile << "printf" << std::endl;
    std::string *num = 0;
    this->getSym();
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    if (this->sym == -1 || this->sym == NONE) {
        getSym();
        return;
    }
    if (this->sym == STRING) {
        int index = -1;
        this->pushString(new std::string(this->token), &index);
        num = new std::string();
        this->int2String(num, index);
        this->getSym();
        if (this->sym == COMMA)
            this->getSym();
        else {
            if (this->sym == RPARENT)
                this->getSym();
            else
                this->errorHandle(RPARENTERROR);
            this->pushMidCode(PRINT, num, ZEROOP, num);
            if (this->sym == SEMICOLON)
                this->getSym();
            else
                this->errorHandle(SEMICOLONERROR);
            return;
        }
    }
    int returnType = NONE;
    std::string temp = std::string();
    this->expressionProcess(&returnType, &temp);
    if (num)
        this->pushMidCode(PRINT, num, ZEROOP, num);
    switch (returnType) {
        case INTSYM:
            this->pushMidCode(PRINT, &temp, new std::string("int"), &temp);
            break;
        case CHARSYM:
            this->pushMidCode(PRINT, &temp, new std::string("char"), &temp);
            break;
    }
    if (this->sym == RPARENT)
        this->getSym();
    else {
        this->errorHandle(RPARENTERROR);
        this->skip(SEMICOLON);
    }
}

void Compiler::returnProcess(bool *flag, int returnType, std::string *name) {
    this->syntaxOutFile << "return" << std::endl;
    this->getSym();
    if (this->sym == LPARENT) {
        this->getSym();
        int returnType2 = NONE;
        std::string temp = std::string();
        this->expressionProcess(&returnType2, &temp);
        if (returnType == VOIDSYM)
            this->errorHandle(RETURNEXTRAERROR);
        else {
            if (this->isOperandTemp(&temp)) {
                midCode *code = this->midCodes[this->midCodeIndex - 1];
                *code->res = std::string("#RET");
            } else {
                this->pushMidCode(ADD, &temp, ZEROOP, new std::string("#RET"));
            }
            if (returnType != returnType2)
                this->errorHandle(RETURNERROR);
        }
        *flag = true;
        if (this->sym == RPARENT)
            this->getSym();
        else
            this->errorHandle(RPARENTERROR);
    }
    if (returnType != VOIDSYM && !(*flag))
        this->errorHandle(RETURNERROR);
    std::stringstream stringStream = std::stringstream();
    stringStream << *name << "$end";
    std::string s = stringStream.str();
    if (!this->isEqual(std::string("main"), *name))
        this->pushMidCode(GOTO, new std::string(), new std::string(), &s);
    else
        this->pushMidCode(EXIT, new std::string(), new std::string(), new std::string());
}

void Compiler::doWhileProcess(bool *flag, int returnType, std::string *name) {
    this->syntaxOutFile << "do statement" << std::endl;
    std::string *doLabel = new std::string();
    std::string *endLabel = new std::string();
    this->genLabel(doLabel);
    this->genLabel(endLabel);
    this->pushMidCode(LABEL, new std::string(), new std::string(), doLabel);
    this->getSym();
    if (this->isInTarget(STATEMENT, STATEMENT_SIZE))
        this->statementProcess(flag, returnType, name);
    else
        this->errorHandle(STATEMENTERROR);
    if (this->sym == WHILESYM) {
        this->syntaxOutFile << "while statement" << std::endl;
        this->getSym();
        if (this->sym == LPARENT)
            this->getSym();
        else
            this->errorHandle(LPARENTERROR);
        this->conditionProcess(endLabel);
        if (this->sym == RPARENT)
            this->getSym();
        else {
            this->errorHandle(RBRACEERROR);
            this->skip(STATEMENT, STATEMENT_SIZE);
        }
    } else
        this->errorHandle(NOWHILEERROR);
    this->pushMidCode(GOTO, new std::string(), new std::string(), doLabel);
    this->pushMidCode(LABEL, new std::string(), new std::string(), endLabel);
}

void Compiler::forProcess(bool *flag, int returnType, std::string *name) {
    this->syntaxOutFile << "for statement" << std::endl;
    std::string *forLabel = new std::string();
    std::string *endLabel = new std::string();
    this->genLabel(forLabel);
    this->genLabel(endLabel);
    this->getSym();
    int tempOp;
    if (this->sym == LPARENT) {
        this->getSym();
        if (this->sym == ID) {
            this->forAssignProcess(flag, returnType, new std::string(this->token), true);
        } else {
            this->errorHandle(IDERROR);
            this->skip(SEMICOLON);
        }
        this->pushMidCode(LABEL, new std::string(), new std::string(), forLabel);
        this->conditionProcess(endLabel);
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
        if (this->sym == ID) {
            this->forAssignProcess(flag, returnType, new std::string(this->token), false);
            midCode *code = this->midCodes[this->midCodeIndex - 1];
            tempOp = code->op;
            code->op = NONE;
        } else {
            this->errorHandle(IDERROR);
            this->skip(SEMICOLON);
        }
        this->statementProcess(flag, returnType, name);
    } else
        this->errorHandle(LPARENTERROR);
    this->switchMidCode(tempOp);
    this->pushMidCode(GOTO, new std::string(), new std::string(), forLabel);
    this->pushMidCode(LABEL, new std::string(), new std::string(), endLabel);
    this->syntaxOutFile << "for statement end" << std::endl;
}

void Compiler::forAssignProcess(bool *flag, int returnType, std::string *name, bool first) {
    symbol *sym = 0;
    if (!this->find(name, &sym, false)) {
        this->errorHandle(IDDEFINEERROR);
        this->skip(SEMICOLON);
        return;
    }
    this->getSym();
    if (this->sym == ASSIGN) {
        this->syntaxOutFile << "for assign statement" << std::endl;
        if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
            this->errorHandle(SIMPLEVARERROR);
        this->getSym();
        int returnType2 = NONE;
        std::string operand = std::string();
        this->expressionProcess(&returnType2, &operand);
        if (sym->returnType == CHARSYM && returnType2 == INTSYM)
            this->errorHandle(ILLEGALASSERROR);
        if (this->isOperandTemp(&operand)) {
            midCode *code = this->midCodes[this->midCodeIndex - 1];
            *code->res = *sym->name;
        } else {
            this->pushMidCode(ADD, &operand, ZEROOP, sym->name);
        }
        if (first) {
            if (this->sym == SEMICOLON)
                this->getSym();
            else this->errorHandle(SEMICOLON);
        } else {
            if (this->sym == RPARENT)
                this->getSym();
            else {
                this->errorHandle(RPARENTERROR);
                this->skip(STATEMENT, STATEMENT_SIZE);
            }
        }
    } else
        this->errorHandle(ASSIGNERROR);

}

void Compiler::assignOrFuncProcess(bool *flag, int returnType, std::string *name) {
    symbol *sym = 0;
    if (!this->find(name, &sym, false)) {
        this->errorHandle(IDDEFINEERROR);
        this->skip(SEMICOLON);
        return;
    }
    this->getSym();
    if (this->sym == LPARENT) {
        this->syntaxOutFile << "func statement" << std::endl;
        if (sym->symbolType != FUNCSYM)
            this->errorHandle(FUNCERROR);
        this->getSym();
        if (this->sym != RPARENT)
            this->paraListProcess(sym);
        pushMidCode(CALL, new std::string(), new std::string(), sym->name);
        if (this->sym == RPARENT)
            this->getSym();
        else
            this->errorHandle(RPARENTERROR);
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
    } else if (this->sym == ASSIGN) {
        this->syntaxOutFile << "assign statement" << std::endl;
        if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
            this->errorHandle(SIMPLEVARERROR);
        this->getSym();
        int returnType2 = NONE;
        std::string operand = std::string();
        this->expressionProcess(&returnType2, &operand);
        if (sym->returnType == CHARSYM && returnType2 == INTSYM)
            this->errorHandle(ILLEGALASSERROR);
        if (this->isOperandTemp(&operand)) {
            midCode *code = this->midCodes[this->midCodeIndex - 1];
            *code->res = *sym->name;
        } else {
            this->pushMidCode(ADD, &operand, ZEROOP, sym->name);
        }
        if (this->sym == SEMICOLON)
            this->getSym();
        else this->errorHandle(SEMICOLON);
    } else if (this->sym == LBRACK) {
        this->syntaxOutFile << "assign statement" << std::endl;
        if (sym->symbolType != ARRAYSYM)
            this->errorHandle(ARRAYERROR);
        this->getSym();
        int returnType2 = NONE;
        std::string operand = std::string();
        this->expressionProcess(&returnType2, &operand);
        if (this->isOperandNum(&operand)) {
            int index = atoi(operand.c_str());
            if (index >= sym->feature)
                this->errorHandle(ARRAYOUTERROR);
        }
        if (this->sym == RBRACK)
            this->getSym();
        else
            this->errorHandle(RBRACKERROR);
        if (this->sym == ASSIGN)
            this->getSym();
        else
            this->errorHandle(ASSIGNERROR);
        int returnType3 = NONE;
        std::string operand2 = std::string();
        this->expressionProcess(&returnType3, &operand2);
        if (sym->returnType == CHARSYM && returnType3 == INTSYM)
            this->errorHandle(ILLEGALASSERROR);
        this->pushMidCode(LARRAY, &operand2, &operand, name);
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
    } else if (this->sym == SEMICOLON) {
        if (sym->symbolType != FUNCSYM || sym->feature != 0)
            this->errorHandle(NOPARAFUNCERROR);
        this->pushMidCode(CALL, new std::string(), new std::string(), name);
        this->getSym();
    } else
        this->errorHandle(SEMICOLONERROR);
}

void Compiler::statementProcess(bool *flag, int returnType, std::string *funcName) {
    std::string *name = new std::string(this->token);
    switch (this->sym) {
        case IFSYM:
            this->ifProcess(flag, returnType, funcName);
            break;
        case DOSYM:
            this->doWhileProcess(flag, returnType, funcName);
            break;
        case FORSYM:
            this->forProcess(flag, returnType, funcName);
            break;
        case SCANFSYM:
            this->scanfProcess();
            if (this->sym == SEMICOLON)
                this->getSym();
            else
                this->errorHandle(SEMICOLONERROR);
            break;
        case PRINTFSYM:
            this->printfProcess();
            break;
        case RETURNSYM:
            this->returnProcess(flag, returnType, funcName);
            if (this->sym == SEMICOLON)
                this->getSym();
            else
                this->errorHandle(SEMICOLONERROR);
            break;
        case LBRACE:
            this->getSym();
            this->statementsProcess(flag, returnType, funcName);
            if (this->sym == RBRACE)
                this->getSym();
            else
                this->errorHandle(RBRACEERROR);
            break;
        case ID:
            this->assignOrFuncProcess(flag, returnType, name);
            break;
        case SEMICOLON:
            this->getSym();
            break;
    }
}

void Compiler::statementsProcess(bool *flag, int returnType, std::string *name) {
    while (this->isInTarget(STATEMENT, STATEMENT_SIZE))
        this->statementProcess(flag, returnType, name);
}

void Compiler::compoundProcess(bool *flag, int returnType, std::string *name) {
    if (this->sym == CONSTSYM)
        this->constState();
    if (this->isInTarget(DEF, DEF_SIZE))
        this->varState();
    this->statementsProcess(flag, returnType, name);
}

void Compiler::noParaFuncDef(symbol *sym) {
    if (this->sym == LBRACE)
        this->getSym();
    else
        this->errorHandle(LBRACEERROR);
    bool flag = false;
    this->pushMidCode(FUNC, new std::string(), new std::string(), sym->name);
    this->compoundProcess(&flag, sym->returnType, sym->name);
    if (this->sym == RBRACE) {
        this->getSym();
        if (!flag && sym->returnType != VOIDSYM)
            this->errorHandle(RETURNMISSERROR);
    } else
        this->errorHandle(RBRACEERROR);
    std::stringstream stringStream = std::stringstream();
    stringStream << *sym->name << "$end";
    std::string s = stringStream.str();
    this->pushMidCode(LABEL, new std::string(), new std::string(), &s);
    this->pushMidCode(RET, new std::string(), new std::string(), sym->name);
}

void Compiler::paraFuncDef(symbol *sym) {
    this->syntaxOutFile << "func def" << std::endl;
    this->getSym();
    if (this->sym != RPARENT)
        this->paraProcess(sym);
    if (this->sym == RPARENT)
        this->getSym();
    else {
        this->errorHandle(RPARENTERROR);
        this->skip(STATEMENT, STATEMENT_SIZE);
    }
    this->noParaFuncDef(sym);
    this->syntaxOutFile << "func def end" << std::endl;
}

void Compiler::voidFuncDef() {
    int returnType = VOIDSYM;
    std::string *name = new std::string(this->token);
    symbol *sym = 0;
    if (this->find(name, &sym, true))
        this->errorHandle(DUPLICATEERROR);
    else
        sym = this->push(name, returnType, FUNCSYM, 0, this->line);
    this->getSym();
    this->prepareFunc();
    if (this->sym == LPARENT)
        this->paraFuncDef(sym);
    else {
        this->errorHandle(LPARENTERROR);
        this->skip(STATEMENT, STATEMENT_SIZE);
        this->noParaFuncDef(sym);
    }
    this->pop();
}

void Compiler::mainDef() {
    this->syntaxOutFile << "main" << std::endl;
    std::string *name = new std::string("main");
    if (this->sym == MAINSYM)
        this->getSym();
    else {
        this->errorHandle(MAINERROR);
        this->getSym();
    }
    this->push(name, VOIDSYM, FUNCSYM, 0, this->line);
    if (this->sym == LPARENT)
        this->getSym();
    else {
        this->errorHandle(LPARENTERROR);
    }
    if (this->sym == RPARENT)
        this->getSym();
    else
        this->errorHandle(RPARENTERROR);
    if (this->sym == LBRACE) {
        this->prepareFunc();
        this->getSym();
    } else
        this->errorHandle(LBRACEERROR);
    bool flag = false;
    this->pushMidCode(FUNC, new std::string(), new std::string(), new std::string("main"));
    this->compoundProcess(&flag, VOIDSYM, name);
    if (this->sym == RBRACE) {
        this->pop();
        this->pushMidCode(EXIT, new std::string(), new std::string(), new std::string());
        return;
    } else
        this->errorHandle(RBRACEERROR);
}

void Compiler::afterVar() {
    if (this->sym == -1)
        return;
    else if (this->sym == VOIDSYM) {
        this->getSym();
        if (this->sym == ID) {
            this->voidFuncDef();
            this->afterVar();
        } else {
            this->mainDef();
            mainFlag = true;
        }
    } else if (this->sym == INTSYM || this->sym == CHARSYM) {
        std::string *name = 0;
        int returnType = NONE;
        symbol *sym = 0;
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        if (this->find(name, &sym, true))
            this->errorHandle(DUPLICATEERROR);
        else
            sym = this->push(name, returnType, FUNCSYM, 0, this->line);
        this->prepareFunc();
        if (this->sym == LPARENT)
            this->paraFuncDef(sym);
        else
            this->errorHandle(LPARENTERROR);
        this->pop();
        this->afterVar();
    } else
        this->errorHandle(UNKNOWNERROR);
}

void Compiler::afterConst() {
    if (this->sym == -1)
        return;
    else if (this->sym == VOIDSYM) {
        this->getSym();
        if (this->sym == ID) {
            this->voidFuncDef();
            this->afterVar();
        } else {
            this->mainDef();
            mainFlag = true;
        }
    } else if (this->sym == INTSYM || this->sym == CHARSYM) {
        std::string *name = 0;
        int returnType = 0;
        symbol *sym = 0;
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        if (this->isInTarget(VARDEF, VARDEF_SIZE)) {
            this->varDef(returnType, name);
            this->afterConst();
        } else if (this->sym == LPARENT) {
            symbol *sym = 0;
            if (this->find(name, &sym, true))
                this->errorHandle(DUPLICATEERROR);
            else
                sym = this->push(name, returnType, FUNCSYM, 0, this->line);
            this->prepareFunc();
            this->paraFuncDef(sym);
            this->pop();
            this->afterVar();
        } else {
            symbol *sym = 0;
            if (this->find(name, &sym, true))
                this->errorHandle(DUPLICATEERROR);
            else
                sym = this->push(name, returnType, FUNCSYM, 0, this->line);
            this->prepareFunc();
            this->paraFuncDef(sym);
            this->pop();
            this->afterVar();
        }
    }
}

void Compiler::analyze() {
    this->syntaxOutFile << "syntax analyze start" << std::endl;
    this->getSym();
    if (this->sym == CONSTSYM) this->constState();
    this->afterConst();
    if (!this->mainFlag)
        this->errorHandle(MAINERROR);
    this->syntaxOutFile << "syntax analyze end" << std::endl;
}
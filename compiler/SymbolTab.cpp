//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include <sstream>
#include "SymbolTab.h"
#include "Compiler.h"
#include "definition.h"

unsigned int Compiler::hash(const char *str) {
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str) {
        char c = *str;
        hash = hash * seed + (c);
        str++;
    }
    return (hash & 0x00000FFF);
}

bool Compiler::isEqual(std::string id1, std::string id2) {
    std::string::iterator p = id1.begin();
    std::string::iterator q = id2.begin();
    while (p != id1.end() && q != id2.end() && *p == *q) {
        ++p;
        ++q;
    }
    return p == id1.end() && q == id2.end();
}

bool Compiler::find(std::string *name, symbol **sym, bool local) {
    int hashIndex = this->hash(name->c_str());
    int symbolIndex = this->symbolHash[hashIndex];
    while ((local && symbolIndex >= this->index) || (!local && symbolIndex >= 0)) {
        symbol *temp = this->symbolTab[symbolIndex];
        if (this->isEqual(*(temp->name), *name)) {
            *sym = temp;
            return true;
        }
        symbolIndex = temp->link;
    }
    if (this->index != 0 && local) {
        symbol *funcSymbol = this->symbolTab[this->index - 1];
        if (this->isEqual(*(funcSymbol->name), *name)) {
            *sym = funcSymbol;
            return true;
        }
    }
    return false;
}

void Compiler::prepareFunc() {
    this->index = this->top;
    this->globalAddress = this->address;
    this->address = 0;
}

void Compiler::pushString(std::string *str, int *index) {
    for (int i = 0; i < this->stringNum; i++) {
        std::string *temp = this->stringTab[i];
        if (this->isEqual(*temp, *str)) {
            *index = i;
            return;
        }
    }
    *index = this->stringNum;
    this->stringTab[this->stringNum++] = str;
}

void Compiler::pop() {
    this->funcSymbolNum[this->funcNum] = this->top - this->index;
    this->funcSymbolTab[this->funcNum] = new symbol *[500];
    while (this->top > this->index) {
        this->top--;
        symbol *sym = this->symbolTab[this->top];
        int index = hash(sym->name->c_str());
        this->symbolHash[index] = sym->link;
        this->funcSymbolTab[this->funcNum][this->top - this->index] = sym;
    }
    this->symbolTab[this->top - 1]->ref = this->funcNum;
    this->funcMaxAddress[this->funcNum] = this->address;
    this->index = 0;
    this->address = this->globalAddress;
    this->funcNum++;
}

symbol *Compiler::push(std::string *name, int returnType, int symbolType, int feature, int line) {
    int hashIndex = this->hash(name->c_str());
    int link = this->symbolHash[hashIndex];
    this->symbolHash[hashIndex] = this->top;
    symbol *sym = new symbol();
    sym->name = new std::string();
    *sym->name = *name;
    sym->returnType = returnType;
    sym->symbolType = symbolType;
    sym->feature = feature;
    sym->line = line;
    sym->link = link;
    sym->address = this->address;
    sym->reg = -1;
    switch (symbolType) {
        case CONSTSYM:
            this->address++;
            break;
        case SIMPLESYM:
        case PARASYM:
            this->address++;
            for (int i = 0; i < MAXBLOCK; i++) sym->flag[i] = false;
            break;
        case ARRAYSYM:
            this->address += sym->feature;
            break;
    }
    this->symbolTab[this->top++] = sym;
    return sym;
}

void Compiler::outputSymbol() {
    std::stringstream  stringStream = std::stringstream();
    for(int i=0;i<this->funcNum;i++){
        symbol **tab = this->funcSymbolTab[i];
        int num = this->funcSymbolNum[i];
        for(int j=0;j<num;j++){
            symbol *sym = tab[j];
            stringStream << j << " " << *(sym->name) << " " << sym->line+1 << " ";
            switch (sym->symbolType){
                case CONSTSYM:
                    stringStream<<"常量 ";
                    break;
                case SIMPLESYM:
                    stringStream<<"简单变量 ";
                    break;
                case ARRAYSYM:
                    stringStream<<"数组 ";
                    break;
                case PARASYM:
                    stringStream<<"参数 ";
                    break;
                case FUNCSYM:
                    stringStream<<"函数 ";
                    break;
            }
            switch (sym->returnType){
                case INTSYM:
                    stringStream<<"int ";
                    break;
                case CHARSYM:
                    stringStream<<"char ";
                    break;
                case VOIDSYM:
                    stringStream<<"void ";
                    break;
            }
            stringStream<<sym->feature<<" "<<sym->address<<" ";
            if(sym->reg == -1)
                stringStream<<"无寄存器"<<std::endl;
            else
                stringStream<< (sym->reg<(MAXREG/2)?"$t":"$s") << sym->reg%(MAXREG/2)<<std::endl;
        }
    }
    for(int i=0;i<this->top;i++){
        symbol *sym = this->symbolTab[i];
        stringStream << i << " " << *(sym->name) << " " << sym->line+1 << " ";
        switch (sym->symbolType){
            case CONSTSYM:
                stringStream<<"常量 ";
                break;
            case SIMPLESYM:
                stringStream<<"简单变量 ";
                break;
            case ARRAYSYM:
                stringStream<<"数组 ";
                break;
            case PARASYM:
                stringStream<<"参数 ";
                break;
            case FUNCSYM:
                stringStream<<"函数 ";
                break;
        }
        switch (sym->returnType){
            case INTSYM:
                stringStream<<"int ";
                break;
            case CHARSYM:
                stringStream<<"char ";
                break;
            case VOIDSYM:
                stringStream<<"void ";
                break;
        }
        stringStream<<sym->feature<<" "<<sym->address<<" ";
        if(sym->reg == -1)
            stringStream<<"无寄存器"<<std::endl;
        else
            stringStream<< (sym->reg<(MAXREG/2)?"$t":"$s") << sym->reg%(MAXREG/2)<<std::endl;
    }
    this->symbolOutFile<<stringStream.str()<<std::endl;
}
//
// Created by JJJJJJJiyun on 2018/11/27.
//

#include <sstream>
#include "MipsCode.h"
#include "Compiler.h"
#include "definition.h"

void Compiler::pushCode(std::string *code) {
    this->mipsCodes[this->mipsIndex] = code;
    this->mipsOutFile << *(this->mipsCodes[this->mipsIndex++]) << std::endl;
}

void Compiler::generateCode(std::string *code) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code;
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::generateCode(std::string *code, std::string *rd, std::string *rs, std::string *rt) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code << " " << *rd << ", " << *rs << ", " << *rt;
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::generateCode(std::string *code, std::string *rd, std::string *rt, int immediate) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code << " " << *rd << ", " << *rt << ", " << immediate;
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::generateCode(std::string *code, std::string *target) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code << " " << *target;
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::generateCode(std::string *code, std::string *rs, int num, std::string *rt) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code << " " << *rs << ", " << num << "(" << *rt << ")";
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::generateCode(std::string *code, std::string *rs, std::string *label) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code << " " << *rs << ", " << *label;
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::generateCode(std::string *code, std::string *rs, int num) {
    std::stringstream stringStream = std::stringstream();
    stringStream << *code << " " << *rs << ", " << num;
    std::string *s = new std::string(stringStream.str());
    this->pushCode(s);
}

void Compiler::initAscii() {
    this->generateCode(new std::string(".data"));
    for(int i=0;i<stringNum;i++){
        std::string *string = this->stringTab[i];
        std::stringstream stringStream = std::stringstream();
        stringStream << "str" << i << ":" << " .asciiz" << " \"" << *string << "\"" ;
        std::string s = stringStream.str();
        this->generateCode(&s);
    }
    std::stringstream stringStream = std::stringstream();
    stringStream << "break" << ":" << " .asciiz " << "\"\\n\"";
    std::string s = stringStream.str();
    this->generateCode(&s);
}

void Compiler::outputMips() {
    for(int i=0;i<this->mipsIndex;i++)
        this->mipsOutFile << *(this->mipsCodes[i]) << std::endl;
}

void Compiler::str2Lower(std::string *oldStr, std::string *newStr) {
    if(!newStr)
        newStr = new std::string();
    for(int i=0;i<oldStr->length();i++){
        char c = tolower((*oldStr)[i]);
        newStr->append(1,c);
    }
}

void Compiler::gotoProcess(std::string *label) {
    std::string *newLabel = new std::string();
    this->str2Lower(label,newLabel);
    this->generateCode(j,newLabel);
    this->generateCode(nop);
}

void Compiler::genMipsLabel(std::string *label) {
    std::string *newLabel = new std::string();
    this->str2Lower(label,newLabel);
    *newLabel = *newLabel+":";
    this->pushCode(newLabel);
    delete newLabel;
}

void Compiler::funcProcess(std::string *name) {
    symbol *sym = 0;
    this->find(name, &sym, false);
    this->genMipsLabel(sym->name);
    int currentAddress = this->funcMaxAddress[sym->ref];
    if(sym->feature!=0)
        this->generateCode(addi,sp,sp,sym->feature*4);
    for(int i=0;i<MAXREG;i++){
        std::stringstream stringStream = std::stringstream();
        int index = i % (MAXREG/2);
        const char *sym = i>=(MAXREG/2)?"$s":"$t";
        stringStream << sym << index;
        std::string *s = new std::string(stringStream.str());
        this->generateCode(sw,s,-currentAddress*4,sp);
        currentAddress++;
    }
    this->generateCode(sw,fp,-currentAddress*4,sp);
    currentAddress++;
    this->generateCode(sw,ra,-currentAddress*4,sp);
    currentAddress++;
    this->generateCode(add,fp,sp,r0);
    this->generateCode(addi,sp,sp,-currentAddress*4);
}

void Compiler::findSym(std::string *name, symbol **resultSym, bool *flag) {
    symbol **symTab = this->funcSymbolTab[this->currentRef];
    int length = this->funcSymbolNum[this->currentRef];
    for(int i=0;i<length;i++){
        symbol *sym = symTab[i];
        if(this->isEqual(*name,*(sym->name))){
            *resultSym = sym;
            *flag = false;
            return;
        }
    }
    for(int i=0;i<this->top;i++){
        symbol *sym = this->symbolTab[i];
        if(this->isEqual(*name,*(sym->name))){
            *resultSym = sym;
            *flag = true;
            return;
        }
    }
}

void Compiler::getUseReg(std::string *rs, std::string *reg) {
    if(this->isOperandReturn(rs))
        *reg = *v0;
    else if(this->isOperandNum(rs)){
        if((*rs)[0]=='0')
            *reg = *r0;
        else
            this->generateCode(li,reg,rs);
    }
    else{
        bool flag = false;
        symbol *sym = 0;
        this->findSym(rs,&sym,&flag);
        int regIndex = sym->reg;
        if(regIndex == -1){
            int offset = sym->address;
            if(flag)
                this->generateCode(lw,reg,4*offset,gp);
            else
                this->generateCode(lw,reg,-offset*4,fp);
        }
        else{
            std::stringstream stringStream = std::stringstream();
            stringStream << (regIndex<(MAXREG/2)?"$t":"$s") << regIndex%(MAXREG/2);
            *reg = stringStream.str();
            if(sym->symbolType == PARASYM && (!this->regs[regIndex] || !this->isEqual(*(this->regs[regIndex]),*sym->name)))
                this->generateCode(lw,reg,-sym->address*4,fp);
            this->regs[regIndex] = sym->name;
        }
    }
}

void Compiler::branchProcess(midCode *code) {
    std::string *op1 = code->op1;
    std::string *op2 = code->op2;
    std::string *reg1 = new std::string();
    *reg1 = *t9;
    std::string *reg2 = new std::string();
    *reg2 = *t8;
    std::string *resReg = new std::string();
    *resReg = *t7;
    if(code->op == EQU || code->op == NEQU){
        if(this->isOperandNum(op1)){
            if(this->isOperandNum(op2)){
                int value1 = atoi(op1->c_str());
                int value2 = atoi(op2->c_str());
                value2 = value1-value2;
                std::string constValue = std::string();
                this->int2String(&constValue,value2);
                this->getUseReg(&constValue,reg1);
                *reg2 = *r0;
            }
            else{
                this->getUseReg(op1,reg1);
                this->getUseReg(op2,reg2);
            }
        }
        else{
            this->getUseReg(op1,reg1);
            this->getUseReg(op2,reg2);
        }
        this->generateCode(code->op == EQU?beq:bne,reg1,reg2,code->res);
    }
    else{
        if(!this->isOperandNum(op1)){
            this->getUseReg(op1,reg1);
            if(this->isOperandNum(op2))
                this->generateCode(subi,resReg,reg1,op2);
            else{
                this->getUseReg(op2,reg2);
                this->generateCode(sub,resReg,reg1,reg2);
            }
        }
        else{
            if(this->isOperandNum(op2)){
                int value1 = atoi(op1->c_str());
                int value2 = atoi(op2->c_str());
                value2 = value1-value2;
                std::string constValue = std::string();
                this->int2String(&constValue,value2);
                this->getUseReg(&constValue,resReg);
            }
            else{
                this->getUseReg(op2,reg2);
                this->getUseReg(op1,reg1);
                this->generateCode(sub,resReg,reg1,reg2);
            }
        }
    }
    switch(code->op) {
        case GREEQU:
            this->generateCode(bgez,resReg,code->res);
            break;
        case GRE:
            this->generateCode(bgtz,resReg,code->res);
            break;
        case LEEQU:
            this->generateCode(blez,resReg,code->res);
            break;
        case LE:
            this->generateCode(bltz,resReg,code->res);
            break;
    }
    this->generateCode(nop);
    delete resReg;
    delete reg1;
    delete reg2;
}

void Compiler::paraProcess(std::string *para) {
    std::string *resReg = new std::string();
    *resReg = *t7;
    this->getUseReg(para,resReg);
    this->generateCode(sw,resReg,0,sp);
    this->generateCode(addi,sp,sp,-4);
    delete resReg;
}

void Compiler::getResultReg(std::string *rd, std::string *reg) {
    if(this->isOperandReturn(rd))
        *reg = *v0;
    else{
        bool flag = false;
        symbol *sym = 0;
        this->findSym(rd,&sym,&flag);
        int regIndex = sym->reg;
        if(!regIndex == -1){
            std::stringstream stringStream = std::stringstream();
            stringStream << (regIndex<(MAXREG/2)?"$t":"$s") << regIndex % (MAXREG/2);
            *reg = stringStream.str();
            this->regs[regIndex] = sym->name;
        }
    }
}

void Compiler::writeBack(std::string *rd, std::string *reg) {
    if(!this->isOperandReturn(rd)){
        symbol *sym = 0;
        bool flag = false;
        this->findSym(rd,&sym,&flag);
        if(sym && sym->reg == -1){
            if(flag)
                this->generateCode(sw,reg,4*sym->address,gp);
            else
                this->generateCode(sw,reg,-sym->address*4,fp);
        }
    }
}

void Compiler::rArrayProcess(midCode *code) {
    std::string *reg2 = new std::string();
    *reg2 = *t8;
    std::string *resReg = new std::string();
    *resReg = *t7;
    bool flag = false;
    symbol *sym = 0;
    this->findSym(code->op1,&sym,&flag);
    this->getUseReg(code->op2,reg2);
    this->generateCode(addi,t9,reg2,sym->address);
    this->generateCode(sll,t9,t9,2);
    this->getResultReg(code->res,resReg);
    if(flag){
        this->generateCode(addu,t9,t9,gp);
        this->generateCode(lw,resReg,0,t9);
    }
    else{
        this->generateCode(sub,t9,fp,t9);
        this->generateCode(lw,resReg,0,t9);
    }
    this->writeBack(code->res,resReg);
    delete reg2;
    delete resReg;
}

void Compiler::lArrayProcess(midCode *code) {
    std::string *rs = code->op1;
    std::string *index = code->op2;
    std::string *name = code->res;
    std::string *reg1 = new std::string();
    *reg1 = *t9;
    std::string *reg2 = new std::string();
    *reg2 = *t8;
    bool flag = false;
    symbol *sym = 0;
    this->findSym(name,&sym,&flag);
    this->getUseReg(index,reg2);
    this->generateCode(addi,t7,reg2,sym->address);
    this->generateCode(sll,t7,t7,2);
    this->getUseReg(rs,reg1);
    if(flag){
        this->generateCode(addu,t7,t7,gp);
        this->generateCode(sw,reg1,0,t7);
    }
    else{
        this->generateCode(sub,t7,fp,t7);
        this->generateCode(sw,reg1,0,t7);
    }
    delete reg1;
    delete reg2;
}

void Compiler::callProcess(std::string *name) {
    std::string *newLabel = new std::string();
    this->str2Lower(name,newLabel);
    this->generateCode(jal,newLabel);
    this->generateCode(nop);
    delete newLabel;
}

void Compiler::returnProcess(std::string *name) {
    symbol *sym = 0;
    this->find(name,&sym, false);
    int currentAddress = 1;
    this->generateCode(lw,ra,currentAddress*4,sp);
    currentAddress++;
    this->generateCode(lw,fp,currentAddress*4,sp);
    currentAddress++;
    for(int i=0;i<MAXREG;i++)
        this->regs[i] = 0;
    for(int i=MAXREG-1;i>=0;i--){
        std::stringstream stringStream = std::stringstream();
        int index = i%(MAXREG/2);
        const char *sym = i>=(MAXREG/2)?"$s":"$t";
        stringStream << sym << index;
        std::string *s = new std::string(stringStream.str());
        this->generateCode(lw,s,currentAddress*4,sp);
        currentAddress++;
    }
    currentAddress+=(this->funcMaxAddress[sym->ref]-1);
    this->generateCode(addi,sp,sp,currentAddress*4);
    this->generateCode(jr,ra);
    this->generateCode(nop);
}

void Compiler::multiProcess(midCode *code) {
    std::string *op1 = code->op1;
    std::string *op2 = code->op2;
    std::string *res = code->res;
    std::string *reg1 = new std::string();
    *reg1 = *t9;
    std::string *reg2 = new std::string();
    *reg2 = *t8;
    std::string *resReg = new std::string();
    *resReg = *t7;
    getUseReg(op1,reg1);
    getUseReg(op2,reg2);
    getResultReg(res,resReg);
    if(code->op == MUL)
        this->generateCode(mul,resReg,reg1,reg2);
    else{
        this->generateCode(divide,reg1,reg2);
        this->generateCode(mflo,resReg);
    }
    this->writeBack(res,resReg);
    delete reg1;
    delete reg2;
    delete resReg;
}

void Compiler::addProcess(midCode *code) {
    std::string *op1 = code->op1;
    std::string *op2 = code->op2;
    std::string *res = code->res;
    std::string *reg1 = new std::string();
    *reg1 = *t9;
    std::string *reg2 = new std::string();
    *reg2 = *t8;
    std::string *resReg = new std::string();
    *resReg = *t7;
    if(this->isOperandNum(op1)){
        if(!this->isOperandNum(op2)){
            this->getUseReg(op2,reg2);
            this->getResultReg(res,resReg);
            this->generateCode(addi,resReg,reg2,op1);
        }
        else{
            int value1 = atoi(op1->c_str());
            int value2 = atoi(op2->c_str());
            value2 = value1 + value2;
            this->getResultReg(res,resReg);
            this->generateCode(li,resReg,value2);
        }
    } else{
        this->getUseReg(op1,reg1);
        if(this->isOperandNum(op2)){
            this->getResultReg(res,resReg);
            this->generateCode(addi,resReg,reg1,op2);
        }
        else{
            this->getUseReg(op2,reg2);
            this->getResultReg(res,resReg);
            this->generateCode(add,resReg,reg1,reg2);
        }
    }
    this->writeBack(res,resReg);
    delete reg1;
    delete reg2;
    delete resReg;
}

void Compiler::subProcess(midCode *code) {
    std::string *op1 = code->op1;
    std::string *op2 = code->op2;
    std::string *res = code->res;
    std::string *reg1 = new std::string();
    *reg1 = *t9;
    std::string *reg2 = new std::string();
    *reg2 = *t8;
    std::string *resReg = new std::string();
    *resReg = *t7;
    if(this->isOperandNum(op1)){
        this->getUseReg(op1,reg1);
        this->getUseReg(op2,reg2);
        this->getResultReg(res,resReg);
        this->generateCode(sub,resReg,reg1,reg2);
    }
    else{
        this->getUseReg(op1,reg1);
        if(!this->isOperandNum(op2)){
            this->getUseReg(op2,reg2);
            this->getResultReg(res,resReg);
            this->generateCode(sub,resReg,reg1,reg2);
        }
        else{
            this->getResultReg(res,resReg);
            this->generateCode(subi,resReg,reg1,op2);
        }
    }
    this->writeBack(res,resReg);
    delete reg1;
    delete reg2;
    delete resReg;
}

void Compiler::scanfProcess(midCode *code) {
    if((*code->op2)[0] == 'i')
        this->generateCode(li,v0,5);
    else
        this->generateCode(li,v0,12);
    this->generateCode(syscall);
    std::string *resReg = new std::string();
    *resReg = *t7;
    this->getResultReg(code->res,resReg);
    this->generateCode(add,resReg,v0,r0);
    this->writeBack(code->res,resReg);
}

void Compiler::printfProcess(midCode *code) {
    if(this->isEqual(*code->op2,std::string("0"))){
        this->generateCode(li,v0,4);
        std::stringstream stringStream = std::stringstream();
        stringStream << "str" << *(code->res);
        std::string *s = new std::string(stringStream.str());
        this->generateCode(la,a0,s);
        this->generateCode(syscall);
        this->generateCode(li,v0,4);
        this->generateCode(la,a0,new std::string("break"));
        this->generateCode(syscall);
    } else{
        this->generateCode(li,v0,(*code->op2)[0] == 'i'?1:11);
        std::string *resReg = new std::string();
        *resReg = *t7;
        this->getUseReg(code->res,resReg);
        this->generateCode(add, a0, resReg,r0);
        this->generateCode(syscall);
        this->generateCode(li,v0,4);
        this->generateCode(la,a0,new std::string("break"));
        this->generateCode(syscall);
        delete resReg;
    }
}

void Compiler::exitProcess() {
    this->generateCode(li,v0,10);
    this->generateCode(syscall);
}


void Compiler::generate() {
    this->initAscii();
    this->generateCode(new std::string(".text"));
    this->generateCode(add,fp,sp,r0);
    this->generateCode(addi,gp,gp,0x10000);
    this->gotoProcess(new std::string("main"));
    for(int i=0;i<this->midCodeIndex;i++){
        midCode *code = this->midCodes[i];
        switch(code->op){
            case FUNC:
                this->currentRef++;
                this->funcProcess(code->res);
                break;
            case EQU:
            case NEQU:
            case GRE:
            case GREEQU:
            case LE:
            case LEEQU:
                this->branchProcess(code);
                break;
            case GOTO:
                this->gotoProcess(code->res);
                break;
            case LABEL:
                this->genMipsLabel(code->res);
                break;
            case PARA:
                this->paraProcess(code->res);
                break;
            case RARRAY:
                this->rArrayProcess(code);
                break;
            case LARRAY:
                this->lArrayProcess(code);
                break;
            case CALL:
                this->callProcess(code->res);
                break;
            case RET:
                this->returnProcess(code->res);
                break;
            case DIV:
            case MUL:
                this->multiProcess(code);
                break;
            case ADD:
                this->addProcess(code);
                break;
            case SUB:
                this->subProcess(code);
                break;
            case SCAN:
                this->scanfProcess(code);
                break;
            case PRINT:
                this->printfProcess(code);
                break;
            case EXIT:
                this->exitProcess();
                break;
        }
    }
}

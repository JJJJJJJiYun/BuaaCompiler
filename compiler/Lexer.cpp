//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include "Compiler.h"
#include "Lexer.h"
#include <iostream>


bool Compiler::isEOF() {
    return this->infile.peek() == EOF;
}

void Compiler::freshToken() {
    token = "";
}

void Compiler::getNextLine() {
    getline(infile, inputLine);
    inputLine += '\n';
    line += 1;
    lineLength = inputLine.length();
    current = 0;
}

void Compiler::getChar() {
    while (lineLength == 0 || current >= lineLength) {
        if (infile.good())
            getNextLine();
        else {
            lineLength = 0;
            break;
        }
    }
    if (lineLength > current)
        ch = inputLine.at(current++);
    else {
        sym = 0;
        ch = 0;
    }
}

void Compiler::skip() {
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        getChar();
    }
}

bool Compiler::isLetter() {
    if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z' || ch == '_')
        return true;
    else
        return false;
}

bool Compiler::isDigit() {
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

void Compiler::constructToken() {
    token += ch;
}

int Compiler::isReserve() {
    if (token == "main")
        return MAINSYM;
    else if (token == "int")
        return INTSYM;
    else if (token == "char")
        return CHARSYM;
    else if (token == "const")
        return CONSTSYM;
    else if (token == "void")
        return VOIDSYM;
    else if (token == "if")
        return IFSYM;
    else if (token == "else")
        return ELSESYM;
    else if (token == "do")
        return DOSYM;
    else if (token == "while")
        return WHILESYM;
    else if (token == "for")
        return FORSYM;
    else if (token == "scanf")
        return SCANFSYM;
    else if (token == "printf")
        return PRINTFSYM;
    else if (token == "return")
        return RETURNSYM;
    else
        return 0;
}

bool Compiler::isLegalString() {
    if (ch >= 32 && ch <= 126 && ch != 34)
        return true;
    else {
        errorHandle(TERMINALERROR);
        return false;
    }

}

void Compiler::output() {
    switch (sym) {
        case PLUS:
            lexerOutFile << count++ << " PLUS +" << std::endl;
            break;
        case MINUS:
            lexerOutFile << count++ << " MINUS -" << std::endl;
            break;
        case MULTI:
            lexerOutFile << count++ << " MULTI *" << std::endl;
            break;
        case DIVIDE:
            lexerOutFile << count++ << " divide /" << std::endl;
            break;
        case LESS:
            lexerOutFile << count++ << " LESS <" << std::endl;
            break;
        case LESSEQU:
            lexerOutFile << count++ << " LESSEQU <=" << std::endl;
            break;
        case GREATEQU:
            lexerOutFile << count++ << " GREATEQU >=" << std::endl;
            break;
        case GREAT:
            lexerOutFile << count++ << " GREAT >" << std::endl;
            break;
        case NEQUAL:
            lexerOutFile << count++ << " NEQUAL !=" << std::endl;
            break;
        case EQUAL:
            lexerOutFile << count++ << " EQUAL ==" << std::endl;
            break;
        case ASSIGN:
            lexerOutFile << count++ << " ASSIGN =" << std::endl;
            break;
        case LPARENT:
            lexerOutFile << count++ << " LPARENT (" << std::endl;
            break;
        case RPARENT:
            lexerOutFile << count++ << " RPARENT )" << std::endl;
            break;
        case LBRACK:
            lexerOutFile << count++ << " LBRACK [" << std::endl;
            break;
        case RBRACK:
            lexerOutFile << count++ << " RBRACK ]" << std::endl;
            break;
        case LBRACE:
            lexerOutFile << count++ << " LBRACE {" << std::endl;
            break;
        case RBRACE:
            lexerOutFile << count++ << " RBRACE }" << std::endl;
            break;
        case COMMA:
            lexerOutFile << count++ << " COMMA ," << std::endl;
            break;
        case SEMICOLON:
            lexerOutFile << count++ << " SEMICOLON ;" << std::endl;
            break;
        case ID:
            lexerOutFile << count++ << " ID " + token << std::endl;
            break;
        case UNSIGNEDINT:
            lexerOutFile << count++ << " UNSIGNEDINT " + token << std::endl;
            break;
        case ZERO:
            lexerOutFile << count++ << " ZERO " + token << std::endl;
            break;
        case CHAR:
            lexerOutFile << count++ << " QUOTE '" << std::endl;
            lexerOutFile << count++ << " CHAR " + token << std::endl;
            lexerOutFile << count++ << " QUOTE '" << std::endl;
            break;
        case STRING:
            lexerOutFile << count++ << " DOUQUOTE \"" << std::endl;
            lexerOutFile << count++ << " STRING " + token << std::endl;
            lexerOutFile << count++ << " DOUQUOTE \"" << std::endl;
            break;
        case MAINSYM:
            lexerOutFile << count++ << " MAINSYM main" << std::endl;
            break;
        case INTSYM:
            lexerOutFile << count++ << " INTSYM int" << std::endl;
            break;
        case CHARSYM:
            lexerOutFile << count++ << " CHARSYM char" << std::endl;
            break;
        case CONSTSYM:
            lexerOutFile << count++ << " CONSTSYM const" << std::endl;
            break;
        case VOIDSYM:
            lexerOutFile << count++ << " VOIDSYM void" << std::endl;
            break;
        case IFSYM:
            lexerOutFile << count++ << " IFSYM if" << std::endl;
            break;
        case ELSESYM:
            lexerOutFile << count++ << " ELSESYM else" << std::endl;
            break;
        case DOSYM:
            lexerOutFile << count++ << " DOSYM do" << std::endl;
            break;
        case WHILESYM:
            lexerOutFile << count++ << " WHILESYM while" << std::endl;
            break;
        case FORSYM:
            lexerOutFile << count++ << " FORSYM for" << std::endl;
            break;
        case SCANFSYM:
            lexerOutFile << count++ << " SCANFSYM scanf" << std::endl;
            break;
        case PRINTFSYM:
            lexerOutFile << count++ << " PRINTFSYM printf" << std::endl;
            break;
        case RETURNSYM:
            lexerOutFile << count++ << " RETURNSYM return" << std::endl;
            break;
    }
}

void Compiler::getSym() {
    sym = 0;
    freshToken();
    getChar();
    skip();
    if (isLetter()) { //处理字符串
        while (isLetter() || isDigit()) {
            constructToken();
            getChar();
        }
        current--;//回退
        sym = isReserve() == 0 ? ID : isReserve();
    } else if (isDigit()) { //处理数字
        if (ch == '0') {
            constructToken();
            getChar();
            if (isDigit()) {
                this->errorHandle(FORMERZEROERROR);
                while (isDigit() || isLetter()) {
                    getChar();
                }
                sym = NONE;
                return;
            } else
                sym = ZERO;
        } else {
            while (isDigit() && ch != 0) {
                constructToken();
                getChar();
            }
        }
        if (isLetter()) {
            while (isLetter() || isDigit()) {
                getChar();
            }
            this->errorHandle(FORMERNUMERROR);
            sym = 0;
            return;
        }
        current--;
        sym = UNSIGNEDINT;
    } else if (ch == '\'') { //处理字符
        getChar();
        if (isLetter() || isDigit() || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            sym = CHAR;
            constructToken();
            getChar();
            if (ch != '\'') {
                current--;
                this->errorHandle(SQERROR);
            }
        } else {
            current--;
            this->errorHandle(CHARERROR);
        }
    } else if (ch == '\"') { //处理字符串
        getChar();
        if (ch == '\"') {
            sym = STRING;
            return;
        }
        while (ch != '\"' && isLegalString() && ch != 0) {
            constructToken();
            getChar();
        }
        if (ch == '\"')
            sym = STRING;
        else {
            this->errorHandle(DQERROR);
            sym = 0;
            while (ch != '\"' && ch != 0)
                getChar();    //跳过无用字符
        }
    } else if (ch == '+')
        sym = PLUS;
    else if (ch == '-')
        sym = MINUS;
    else if (ch == '*')
        sym = MULTI;
    else if (ch == '/')
        sym = DIVIDE;
    else if (ch == '(')
        sym = LPARENT;
    else if (ch == ')')
        sym = RPARENT;
    else if (ch == '[')
        sym = LBRACK;
    else if (ch == ']')
        sym = RBRACK;
    else if (ch == '{')
        sym = LBRACE;
    else if (ch == '}')
        sym = RBRACE;
    else if (ch == ',')
        sym = COMMA;
    else if (ch == ';')
        sym = SEMICOLON;
    else if (ch == '<') {
        skip();
        getChar();
        if (ch == '=')
            sym = LESSEQU;
        else {
            current--;
            sym = LESS;
        }
    } else if (ch == '>') {
        skip();
        getChar();
        if (ch == '=')
            sym = GREATEQU;
        else {
            current--;
            sym = GREAT;
        }
    } else if (ch == '!') {
        skip();
        getChar();
        if (ch == '=')
            sym = NEQUAL;
        else {
            current--;
            this->errorHandle(EMERROR);
        }
    } else if (ch == '=') {
        skip();
        getChar();
        if (ch == '=')
            sym = EQUAL;
        else {
            current--;
            sym = ASSIGN;
        }
    } else sym = -1;
    output();
}

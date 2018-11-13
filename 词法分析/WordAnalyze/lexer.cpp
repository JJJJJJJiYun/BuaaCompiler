//
// Created by JJJJJJJiyun on 2018/11/12.
//

#include <stdio.h>
#include "Lexer.h"

string Lexer::path, Lexer::token, Lexer::inputLine;
int Lexer::sym, Lexer::lineLength, Lexer::current, Lexer::line, Lexer::count;
char Lexer::ch;
ifstream Lexer::infile;
ofstream Lexer::outfile;


void Lexer::init() {
    line = 0;
    count = 1;
    lineLength = 0;
    current = 0;
    cin >> path;
    infile.open(path, ios::in);
    outfile.open("output.txt");
}

void Lexer::run() {
    while (infile.good()) {
        getSym();
        output();
    }
}

void Lexer::close() {
    infile.close();
    outfile.close();
}

void Lexer::freshToken() {
    token = "";
}

void Lexer::getNextLine() {
    getline(infile, inputLine);
    inputLine += '\n';
    line += 1;
    lineLength = inputLine.length();
    current = 0;
}

void Lexer::getChar() {
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

void Lexer::skip() {
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        getChar();
    }
}

bool Lexer::isLetter() {
    if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z' || ch == '_')
        return true;
    else
        return false;
}

bool Lexer::isDigit() {
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

void Lexer::constructToken() {
    token += ch;
}

int Lexer::isReserve() {
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

bool Lexer::isLegalString() {
    if (ch >= 32 && ch <= 126 && ch != 34)
        return true;
    else
        return false;
}

void Lexer::output() {
    switch (sym) {
        case PLUS:
            outfile << count++ << " PLUS +" << endl;
            break;
        case MINUS:
            outfile << count++ << " MINUS -" << endl;
            break;
        case MULTI:
            outfile << count++ << " MULTI *" << endl;
            break;
        case DIVIDE:
            outfile << count++ << " divide /" << endl;
            break;
        case LESS:
            outfile << count++ << " LESS <" << endl;
            break;
        case LESSEQU:
            outfile << count++ << " LESSEQU <=" << endl;
            break;
        case GREATEQU:
            outfile << count++ << " GREATEQU >=" << endl;
            break;
        case GREAT:
            outfile << count++ << " GREAT >" << endl;
            break;
        case NEQUAL:
            outfile << count++ << " NEQUAL !=" << endl;
            break;
        case EQUAL:
            outfile << count++ << " EQUAL ==" << endl;
            break;
        case ASSIGN:
            outfile << count++ << " ASSIGN =" << endl;
            break;
        case LPARENT:
            outfile << count++ << " LPARENT (" << endl;
            break;
        case RPARENT:
            outfile << count++ << " RPARENT )" << endl;
            break;
        case LBRACK:
            outfile << count++ << " LBRACK [" << endl;
            break;
        case RBRACK:
            outfile << count++ << " RBRACK ]" << endl;
            break;
        case LBRACE:
            outfile << count++ << " LBRACE {" << endl;
            break;
        case RBRACE:
            outfile << count++ << " RBRACE }" << endl;
            break;
        case COMMA:
            outfile << count++ << " COMMA ," << endl;
            break;
        case SEMICOLON:
            outfile << count++ << " SEMICOLON ;" << endl;
            break;
        case ID:
            outfile << count++ << " ID " + token << endl;
            break;
        case NUM:
            outfile << count++ << " NUM " + token << endl;
            break;
        case CHAR:
            outfile << count++ << " QUOTE '" << endl;
            outfile << count++ << " CHAR " + token << endl;
            outfile << count++ << " QUOTE '" << endl;
            break;
        case STRING:
            outfile << count++ << " DOUQUOTE \"" << endl;
            outfile << count++ << " STRING " + token << endl;
            outfile << count++ << " DOUQUOTE \"" << endl;
            break;
        case MAINSYM:
            outfile << count++ << " MAINSYM main" << endl;
            break;
        case INTSYM:
            outfile << count++ << " INTSYM int" << endl;
            break;
        case CHARSYM:
            outfile << count++ << " CHARSYM char" << endl;
            break;
        case CONSTSYM:
            outfile << count++ << " CONSTSYM const" << endl;
            break;
        case VOIDSYM:
            outfile << count++ << " VOIDSYM void" << endl;
            break;
        case IFSYM:
            outfile << count++ << " IFSYM if" << endl;
            break;
        case ELSESYM:
            outfile << count++ << " ELSESYM else" << endl;
            break;
        case DOSYM:
            outfile << count++ << " DOSYM do" << endl;
            break;
        case WHILESYM:
            outfile << count++ << " WHILESYM while" << endl;
            break;
        case FORSYM:
            outfile << count++ << " FORSYM for" << endl;
            break;
        case SCANFSYM:
            outfile << count++ << " SCANFSYM scanf" << endl;
            break;
        case PRINTFSYM:
            outfile << count++ << " PRINTFSYM printf" << endl;
            break;
        case RETURNSYM:
            outfile << count++ << " RETURNSYM return" << endl;
            break;
    }
}

void Lexer::getSym() {
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
                cout << "Lex Error: line " << line << ": zero cannot be the first digit of number!" << endl;
                while (isDigit() || isLetter()) {
                    getChar();
                }
                sym = 0;
                return;
            } else
                sym = NUM;
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
            cout << "Lex Error: line " << line << ": ID cannot start with numbers!" << endl;
            sym = 0;
            return;
        }
        current--;
        sym = NUM;
    } else if (ch == '\'') { //处理字符
        getChar();
        if (isLetter() || isDigit() || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            sym = CHAR;
            constructToken();
            getChar();
            if (ch != '\'') {
                current--;
                cout << "Lex Error: line " << line << ": missing quote!" << endl;
            }
        } else {
            current--;
            cout << "Lex Error: line " << line << ": char type error! Content not acceptable!" << endl;
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
            cout << "Lex Error: line " << line << ": string type error! Content not acceptable!" << endl;
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
            cout << "Lex Error: line " << line << ": !" << endl;
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
}

int main() {
    Lexer::init();
    Lexer::run();
    Lexer::close();
    return 0;
}
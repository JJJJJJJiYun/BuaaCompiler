//
// Created by JJJJJJJiyun on 2018/11/12.
//

#include <stdio.h>
#include "Lexer.h"

string Lexer::path, Lexer::token, Lexer::inputLine;
int Lexer::sym, Lexer::lineLength, Lexer::current, Lexer::line, Lexer::count1, Lexer::count2;
char Lexer::ch;
ifstream Lexer::infile;
ofstream Lexer::outfile;


void Lexer::init() {
    line = 0;
    count1 = 1;
    count2 = 1;
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
        outputToFile();
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
            cout << count1++ << " PLUS +" << endl;
            break;
        case MINUS:
            cout << count1++ << " MINUS -" << endl;
            break;
        case MULTI:
            cout << count1++ << " MULTI *" << endl;
            break;
        case DIVIDE:
            cout << count1++ << " divide /" << endl;
            break;
        case LESS:
            cout << count1++ << " LESS <" << endl;
            break;
        case LESSEQU:
            cout << count1++ << " LESSEQU <=" << endl;
            break;
        case GREATEQU:
            cout << count1++ << " GREATEQU >=" << endl;
            break;
        case GREAT:
            cout << count1++ << " GREAT >" << endl;
            break;
        case NEQUAL:
            cout << count1++ << " NEQUAL !=" << endl;
            break;
        case EQUAL:
            cout << count1++ << " EQUAL ==" << endl;
            break;
        case ASSIGN:
            cout << count1++ << " ASSIGN =" << endl;
            break;
        case LPARENT:
            cout << count1++ << " LPARENT (" << endl;
            break;
        case RPARENT:
            cout << count1++ << " RPARENT )" << endl;
            break;
        case LBRACK:
            cout << count1++ << " LBRACK [" << endl;
            break;
        case RBRACK:
            cout << count1++ << " RBRACK ]" << endl;
            break;
        case LBRACE:
            cout << count1++ << " LBRACE {" << endl;
            break;
        case RBRACE:
            cout << count1++ << " RBRACE }" << endl;
            break;
        case COMMA:
            cout << count1++ << " COMMA ," << endl;
            break;
        case SEMICOLON:
            cout << count1++ << " SEMICOLON ;" << endl;
            break;
        case ID:
            cout << count1++ << " ID " + token << endl;
            break;
        case NUM:
            cout << count1++ << " NUM " + token << endl;
            break;
        case CHAR:
            cout << count1++ << " QUOTE '" << endl;
            cout << count1++ << " CHAR " + token << endl;
            cout << count1++ << " QUOTE '" << endl;
            break;
        case STRING:
            cout << count1++ << " DOUQUOTE \"" << endl;
            cout << count1++ << " STRING " + token << endl;
            cout << count1++ << " DOUQUOTE \"" << endl;
            break;
        case MAINSYM:
            cout << count1++ << " MAINSYM main" << endl;
            break;
        case INTSYM:
            cout << count1++ << " INTSYM int" << endl;
            break;
        case CHARSYM:
            cout << count1++ << " CHARSYM char" << endl;
            break;
        case CONSTSYM:
            cout << count1++ << " CONSTSYM const" << endl;
            break;
        case VOIDSYM:
            cout << count1++ << " VOIDSYM void" << endl;
            break;
        case IFSYM:
            cout << count1++ << " IFSYM if" << endl;
            break;
        case ELSESYM:
            cout << count1++ << " ELSESYM else" << endl;
            break;
        case DOSYM:
            cout << count1++ << " DOSYM do" << endl;
            break;
        case WHILESYM:
            cout << count1++ << " WHILESYM while" << endl;
            break;
        case FORSYM:
            cout << count1++ << " FORSYM for" << endl;
            break;
        case SCANFSYM:
            cout << count1++ << " SCANFSYM scanf" << endl;
            break;
        case PRINTFSYM:
            cout << count1++ << " PRINTFSYM printf" << endl;
            break;
        case RETURNSYM:
            cout << count1++ << " RETURNSYM return" << endl;
            break;
    }
}

void Lexer::outputToFile() {
    switch (sym) {
        case PLUS:
            outfile << count2++ << " PLUS +" << endl;
            break;
        case MINUS:
            outfile << count2++ << " MINUS -" << endl;
            break;
        case MULTI:
            outfile << count2++ << " MULTI *" << endl;
            break;
        case DIVIDE:
            outfile << count2++ << " divide /" << endl;
            break;
        case LESS:
            outfile << count2++ << " LESS <" << endl;
            break;
        case LESSEQU:
            outfile << count2++ << " LESSEQU <=" << endl;
            break;
        case GREATEQU:
            outfile << count2++ << " GREATEQU >=" << endl;
            break;
        case GREAT:
            outfile << count2++ << " GREAT >" << endl;
            break;
        case NEQUAL:
            outfile << count2++ << " NEQUAL !=" << endl;
            break;
        case EQUAL:
            outfile << count2++ << " EQUAL ==" << endl;
            break;
        case ASSIGN:
            outfile << count2++ << " ASSIGN =" << endl;
            break;
        case LPARENT:
            outfile << count2++ << " LPARENT (" << endl;
            break;
        case RPARENT:
            outfile << count2++ << " RPARENT )" << endl;
            break;
        case LBRACK:
            outfile << count2++ << " LBRACK [" << endl;
            break;
        case RBRACK:
            outfile << count2++ << " RBRACK ]" << endl;
            break;
        case LBRACE:
            outfile << count2++ << " LBRACE {" << endl;
            break;
        case RBRACE:
            outfile << count2++ << " RBRACE }" << endl;
            break;
        case COMMA:
            outfile << count2++ << " COMMA ," << endl;
            break;
        case SEMICOLON:
            outfile << count2++ << " SEMICOLON ;" << endl;
            break;
        case ID:
            outfile << count2++ << " ID " + token << endl;
            break;
        case NUM:
            outfile << count2++ << " NUM " + token << endl;
            break;
        case CHAR:
            outfile << count2++ << " QUOTE '" << endl;
            outfile << count2++ << " CHAR " + token << endl;
            outfile << count2++ << " QUOTE '" << endl;
            break;
        case STRING:
            outfile << count2++ << " DOUQUOTE \"" << endl;
            outfile << count2++ << " STRING " + token << endl;
            outfile << count2++ << " DOUQUOTE \"" << endl;
            break;
        case MAINSYM:
            outfile << count2++ << " MAINSYM main" << endl;
            break;
        case INTSYM:
            outfile << count2++ << " INTSYM int" << endl;
            break;
        case CHARSYM:
            outfile << count2++ << " CHARSYM char" << endl;
            break;
        case CONSTSYM:
            outfile << count2++ << " CONSTSYM const" << endl;
            break;
        case VOIDSYM:
            outfile << count2++ << " VOIDSYM void" << endl;
            break;
        case IFSYM:
            outfile << count2++ << " IFSYM if" << endl;
            break;
        case ELSESYM:
            outfile << count2++ << " ELSESYM else" << endl;
            break;
        case DOSYM:
            outfile << count2++ << " DOSYM do" << endl;
            break;
        case WHILESYM:
            outfile << count2++ << " WHILESYM while" << endl;
            break;
        case FORSYM:
            outfile << count2++ << " FORSYM for" << endl;
            break;
        case SCANFSYM:
            outfile << count2++ << " SCANFSYM scanf" << endl;
            break;
        case PRINTFSYM:
            outfile << count2++ << " PRINTFSYM printf" << endl;
            break;
        case RETURNSYM:
            outfile << count2++ << " RETURNSYM return" << endl;
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
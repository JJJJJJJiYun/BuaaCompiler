cmake_minimum_required(VERSION 3.12)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(compiler main.cpp Compiler.cpp Compiler.h Lexer.cpp Lexer.h Syntax.cpp Syntax.h definition.h Error.cpp Error.h SymbolTab.cpp SymbolTab.h MidCode.cpp MidCode.h MipsCode.cpp MipsCode.h Optimization.cpp Optimization.h)
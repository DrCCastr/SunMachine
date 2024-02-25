#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <cctype>
#include <sstream>
#include <filesystem>
#include <ostream>


#define tab "    "

#define SUN_ARG_TYPE_NONE 0
#define SUN_ARG_TYPE_STRING 1
#define SUN_ARG_TYPE_EXPR 2

namespace Sun {

class Index {
    public: 
    std::vector<std::string> lexer(std::string FilePath);
    void Machine(std::vector<std::string> Tokens, std::string path);
    bool debug = false;
};

class Str {
    public:
    struct Args
    {
        std::string ToPrint = "";
        std::string Expr = "";
    };
    struct Stats
    {
        bool CanPrint = false;
        bool Argmenting = false;
        int ArgType = SUN_ARG_TYPE_NONE;
    };
    struct compiling
    {
        int Line = 3;
    };
    
};

}

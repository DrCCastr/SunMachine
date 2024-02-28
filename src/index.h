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
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <tinyxml2.h>

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
        std::string ToSystem = "";
        std::string Expr = "";
    };
    struct Stats
    {
        bool CanSystem = false;
        bool Argmenting = false;
        int ArgType = SUN_ARG_TYPE_NONE;
        bool fnNext = true;
        int fnCont = 0;
        bool returning = true;
    };
    
};

}

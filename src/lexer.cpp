#include "index.h"

bool TestNumber(std::string Char) {
    if (Char == "1" or Char == "2" or Char == "3" or Char == "4" or Char == "5" or Char == "6" or Char == "7" or Char == "8" or Char == "9" or Char == "0" or Char == "+") {
        return true;
    }
    return false;
}

std::vector<std::string> Sun::Index::lexer(std::string FilePath) {
    ////// Vars //////
    std::ifstream file(FilePath);
    std::vector<std::string> Tokens;
    
    Sun::Str::Args args;
    Sun::Str::Stats stats;
    //////
    if (file.is_open()) {
        char Char;
        bool AddPrint = false;
        bool Comment = false;
        std::string Character = "";
        std::string tok = "";
        std::string defName = "";
        while (file.get(Char)) {
            if (Index::debug == true) {
                std::cout << Char << " -- " << tok << " -- " << args.Expr << std::endl;
            }
            Character = Char;
            defName += Character;
            if (Character == " ") {
                if (stats.fnNext == true && stats.fnCont == 0) {
                    Tokens.push_back(defName);
                    Tokens.push_back("i32");
                    stats.fnNext = false;
                }
                if (stats.fnNext == true) {
                    stats.fnCont -= 1;
                }
                defName = "";
            } else if (Character == "(") {
                if (!stats.CanSystem) {
                    Tokens.push_back("f2");
                    Tokens.push_back(defName.replace(defName.size() - 1, 1, ""));
                    defName = "";
                }
            } else if (Character == "/") {
                if (Comment == true) {Comment == false;} else {Comment == true;}
            }
            tok += Char;
            if (Comment) {
                tok = "";
                Character = "";
            }
            if (tok ==  " ") {
                tok = "";
            } else if (tok == "{" or tok == "}") {
                tok == "";
            //} else if (tok == "return") {
            //    stats.returning = true;
            //    Tokens.push_back("r1");
            //    Tokens.push_back("i32");
            //    tok = "";
            } else if (tok == "fn") {
                stats.fnNext = true;
                stats.fnCont = 1;
                Tokens.push_back("f1");
                tok = "";
            } else if (tok == "system") {
                stats.CanSystem = true;
                Tokens.push_back("p1");
                tok = "";
            } else if (tok == "(" or tok == ")") {
                tok = "";
                if (stats.CanSystem == true) {
                    //stats.ArgType = SUN_ARG_TYPE_STRING;
                }
                if (stats.Argmenting == true) { stats.Argmenting = false; } else { stats.Argmenting = true; }
            } else if (tok == "\n" or tok == ";" or tok == "\t") {
                tok = "";
            }
            
            if (Character == ",") {
                if (stats.CanSystem == true) {
                    if (stats.Argmenting == true) {
                        AddPrint = true;
                    }
                }
            }
            
            if (TestNumber(Character)) {
                tok = "";
                if ( args.Expr == "" and stats.ArgType != SUN_ARG_TYPE_STRING ) {
                    Tokens.push_back("t1e1");
                }
                if ( !stats.ArgType == SUN_ARG_TYPE_STRING ) {
                    args.Expr += Character;
                }
            }
            
            if (Char == '"' or Character == "'") {
                tok = "";
                AddPrint = false;
                if (stats.Argmenting == true) {
                if (stats.ArgType == SUN_ARG_TYPE_STRING) {
                    stats.ArgType = SUN_ARG_TYPE_NONE;
                } else if (stats.ArgType == SUN_ARG_TYPE_NONE) {
                    stats.ArgType = SUN_ARG_TYPE_STRING;
                    if ( stats.CanSystem == true ) {
                        Tokens.push_back("t1s1");
                    }
                }
                }
            }
            
            /////// Verifica se esta tok = "";argumentando //////
            if (stats.Argmenting == true) {
                ////// Verifica se o a Tipo de argumento e de string
                if (stats.ArgType == SUN_ARG_TYPE_STRING) {
                    if ( Character != "'" and Char != '"' ) {
                        args.ToSystem += Character;
                    }
                    
                    tok = "";
                }
                //////
            }
            //////
            ////// Quando terminar a linha //////
            if(Character == ";"){
                ////// Verifica se tem um print disponivel
                if (stats.returning == true ) {
                    Tokens.push_back(tok.substr(0, 1));
                    stats.returning = false;
                }
                if (args.ToSystem != "" && stats.CanSystem == true) {
                    Tokens.push_back(args.ToSystem);
                    stats.CanSystem = false;
                }
                if (args.Expr != "" and stats.CanSystem == true) {
                    Tokens.push_back(args.Expr);
                }
                //////
                AddPrint = false;
                args.Expr = "";
                args.ToSystem = "";
                stats.CanSystem = false;
                stats.ArgType = SUN_ARG_TYPE_NONE;
                stats.Argmenting = false;
                stats.CanSystem = false;
                tok = "";
            }
            //////
        } 
        
        file.close();
    } else { std::cerr << "Erro ao abrir o arquivo: " << FilePath << std::endl; }
    return Tokens;
}

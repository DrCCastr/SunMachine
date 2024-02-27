#include "index.h"

/*
p1 == print / printar

t1 types/tipos = { -- todos objetos da lista estarao acrensetados a t1 (ex: t1s1)
    s1 = string / texto
    e1 = expr / expresao numerica
}


*/

std::ofstream CreateFile(std::string path, std::vector<std::string> strings_literal) {
    path += "/temp.ll";
    std::ofstream file(path);
    int i = 0;
    
    file << "; arquivo gerado automaticamente\n"
    "; AVISO: Caso mecha em alguma parte inconsientemente pode causar erros ao codigo final\n";
    
    while (i < strings_literal.size()) {
        file << "@.strltr_";
        file << i;
        file << " = private unnamed_addr constant [13 x i8] c\"";
        file << strings_literal[i];
        file << R"(\0A\00)";
        file << "\"\n";
        i++;
    }
    
    file << "declare i32 @puts(i8* nocapture) nounwind\n"
    "define i32 @main() {\n";
    
    return file;
}

void Sun::Index::Machine(std::vector<std::string> Tokens, std::string path) {
    Sun::Str::compiling Compiling;
    int string_literal_index = 0;
    std::vector<std::string> strings_literal;
    int i = 0;
    while (i < Tokens.size()) {
        if (Tokens[i] == "t1s1") {
            strings_literal.push_back(Tokens[i+1]);
        }
        std::cout << Tokens[i] << " -- ";
        i++;
    }
    std::cout << "\n";
    i = 0;
    std::ofstream file = CreateFile(path, strings_literal);
    while (i < Tokens.size())
    {
        if (Tokens[i] == "p1" && i + 2 < Tokens.size()) {
            if (Tokens[i + 1] == "t1s1") { 
                
                file << "\t; Print\n"
                "\t%cast21";
                file << string_literal_index;
                file << " = getelementptr [13 x 18],[13 x i8]*@.strltr_";
                file << string_literal_index;
                file << ", i64 0, i64 0\n"
                "\tcall i32 @puts(i8* %cast21";
                file << string_literal_index;
                file << ")\n";
                
                string_literal_index += 1;
                //Compiling.Line += 1;
                //strings_literal.push_back(Tokens[i+2]);
            } else if (Tokens[i+1] == "t1e1") {
            }
        }
    i++;
    }
    
    file << "\tret 132 0\n"
    "}\n"
    "!0 = !{i32 42, null, !string}\n"
    "!foo = !{!0}\n";
    
    file.close();
    
    system("mkdir temp");
    system("llvm-as temp.ll -o temp/temp.bc");
    system("opt -03 temp/temp.bc -o temp/temp_opt.bc");
    system("llc -03 temp/temp_opt.bc -o temp/temp.s");
    system("gcc -c temp/temp.s -o temp/temp.o");
    system("gcc temp/temp.o -o sun.exe");
    system("rm temp");
}


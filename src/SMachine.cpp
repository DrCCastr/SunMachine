#include "index.h"

/*
p1 = System / chamada do sistema para executar commando no terminal
f1 = fn / funçao / definindo funçao
f2 = fn() / funçao / executar funçao
r1 = return / retorno da funçao

t1 types/tipos = { -- todos objetos da lista estarao acrensetados a t1 (ex: t1s1)
    s1 = string / texto
    e1 = expr / expresao numerica
}


*/

std::ofstream CreateFile(std::string path, std::vector<std::string> strings_literal) {
    path += "/temp/temp.ll";
    std::ofstream file(path);
    int i = 0;
    
    file << "; arquivo gerado automaticamente\n"
    "; AVISO: Caso mecha em alguma parte inconsientemente pode causar erros ao codigo final\n";
    
    while (i < strings_literal.size()) {
        int strLen = strings_literal[i].size() + 1;
        file << "@.strltr_";
        file << i;
        file << " = private unnamed_addr constant [";
        file << strLen;
        file << " x i8] c\"";
        file << strings_literal[i];
        file << R"(\00)";
        file << "\"\n";
        i++;
    }
    
    file << "declare i32 @system(i8*)\n"
    ;//"define i32 @main() {\n";
    
    return file;
}

void Sun::Index::Machine(std::vector<std::string> Tokens, std::string path) {
    int string_literal_index = 0;
    bool first_fn = false;
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
                int strLen = strings_literal[string_literal_index].size() + 1;
                file << "\t; System call\n"
                "\t%cast21";
                file << string_literal_index;
                file << " = getelementptr [";
                file << strLen;
                file << " x i8], [";
                file << strLen;
                file << " x i8]* @.strltr_";
                file << string_literal_index;
                file << ", i32 0, i32 0\n"
                "\t%retval";
                file << string_literal_index;
                file << " = call i32 @system(i8* %cast21";
                file << string_literal_index;
                file << ")\n"
                "\t; End system call\n";
                
                string_literal_index += 1;
                //Compiling.Line += 1;
                //strings_literal.push_back(Tokens[i+2]);
            } else if (Tokens[i+1] == "t1e1") {
            }
        } else if (Tokens[i] == "f1") {
            if (first_fn == true) {
                file << "\tret i32 0 ; Main return\n";
                file << "}\n";
            }
            first_fn = true;
            file << "define ";
            file << Tokens[i+2];
            file << " @";
            file << Tokens[i+1];
            file << "() {\n"; 
        } else if (Tokens[i] == "r1") {
            file << "\tret ";
            file << Tokens[i+1];
            file << " ";
            file << Tokens[i+2];
            file << " ; Return \n";
        } else if (Tokens[i] == "f2") {
            file << "\tcall i32 @";
            file << Tokens[i+1];
            file << "() ; Call function\n";
        }
    i++;
    }
    file << "\tret i32 0 ; Main return\n"
    "}\n";
    file << "!foo = !{!0}\n"
    "!0 = !{i32 42, null, !\"string\"}\n";
    
    file.close();
    
    system("llvm-as temp/temp.ll -o temp/temp.bc");
    system("opt -O3 temp/temp.bc -o temp/temp_opt.bc");
    system("llc -O3 temp/temp_opt.bc -o temp/temp.s");
    system("gcc -c temp/temp.s -o temp/temp.o");
    system("gcc temp/temp.o -o sun.exe");
    system("rm -force temp");
}


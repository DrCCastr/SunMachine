#include "index.h"

/*
p1 == print / printar

t1 types/tipos = { -- todos objetos da lista estarao acrensetados a t1 (ex: t1s1)
    s1 = string / texto
    e1 = expr / expresao numerica
}


*/

std::ofstream CreateFile(std::string path, std::vector<std::string> strings_literal) {
    path += "/temp.s";
    std::ofstream file(path);
    int i = 0;
    
    file << ";bits 64\n"
    "default rel\n"
    "section .bss\n"
    "section .data\n";
    
    while (i < strings_literal.size()) {
        file << "string_literal_";
        file << i;
        file << " db '";
        file << strings_literal[i];
        file << "', 0\n";
        i++;
    }
    
    file << "section .text\n"
    "global _start\n"
    "extern ExitProcess\n"
    "extern printf\n"
    "extern scanf\n"
    "_start:\n"
    "\tPUSH rbp\n"
    "\tMOV rbp, rsp\n"
    "\tSUB rsp, 32\n";
    
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
                file << "\t; print\n";
                file << "\tLEA rcx, string_literal_";
                file << string_literal_index;
                file << "\n";
                file << "\tXOR eax, eax\n";
                file << "\tCALL printf\n";
                file << "\t; end print\n";
                
                string_literal_index += 1;
                //Compiling.Line += 1;
                //strings_literal.push_back(Tokens[i+2]);
            } else if (Tokens[i+1] == "t1e1") {
            }
        }
    i++;
    }
    
    file << "EXIT_LABEL:\n"
    "\tXOR rax, rax\n"
    "\tCALL ExitProcess";
    std::cout << "assembling\n";
    system("nasm -f elf64 temp.s -o temp.o");
    std::cout << "compiling\n";
    system("gcc -o app.exe temp.o -nostdlib -no-pie");
    std::cout << "deleting temp files";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("rm -f temp.s");
    system("rm -f temp.o");
    std::cout << "finalized";
    
    file.close();
}

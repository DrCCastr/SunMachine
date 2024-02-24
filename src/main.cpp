#include "index.h"

std::vector<std::string> GetObjectsFromChar(int argc, char* argv[]) {
    std::vector<std::string> objects;
    for (int i = 2; i < argc; ++i) {
        std::string arg(argv[i]);
        for (char c : arg) {
            objects.push_back(arg);
        }
    }
    return objects;
}

int main(int argc, char *argv[]) {
    Sun::Index index;
    
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::path filePath = currentDir / argv[1];
    
    std::vector<std::string> Tokens = index.lexer(filePath.string());
    index.Machine(Tokens, currentDir.string());
    
    return 0;
}

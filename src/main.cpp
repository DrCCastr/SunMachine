#include "index.h"

using namespace tinyxml2;

int main(int argc, char *argv[]) {
    Sun::Index index;
    
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::path filePath = currentDir / argv[1];
    
    XMLDocument doc;
    doc.LoadFile(filePath.string().c_str());
    const char* file = doc.FirstChildElement("body")->FirstChildElement("file")->GetText();
    
    std::filesystem::path fileCompile = currentDir / file;
    std::vector<std::string> Tokens = index.lexer(fileCompile.string());
    index.Machine(Tokens, currentDir.string());
    
    return 0;
}

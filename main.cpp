#include <iostream>
#include <fstream>  
#include <sstream>  
#include <string>
#include <filesystem>
#include "Interpreter.h"

bool hasExtension(const std::string& filename, const std::string& extension) {
    std::string ext = extension;
    if (ext[0] != '.') {
        ext = "." + ext;
    }
    
    if (filename.length() >= ext.length()) {
        return filename.compare(filename.length() - ext.length(), ext.length(), ext) == 0;
    }
    return false;
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: file cannot open ");
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); 
    return buffer.str();    
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Using: " << argv[0] << " <path_to_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    if (!hasExtension(filename, "chago")) {
        std::cerr << "Error: File must have extension .chago" << std::endl;
        return 1;
    }

    try {
        std::string sourceCode = readFile(filename);

        Interpreter interpreter(sourceCode);
        interpreter.interpret();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
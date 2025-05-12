#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include <iostream>

using std::string;
using std::vector;
using std::map;
using std::cout;

class RessourceLoader {
private:

public:
    const void LoadFiles() {
        const std::filesystem::path ressourcePath{ "Ressources"};

        for (const auto& entry : std::filesystem::directory_iterator(ressourcePath)) {
            const auto filenameStr = entry.path().filename().string();
            if (entry.is_directory()) {
                std::cout << "dir:  " << filenameStr << '\n';
            }
            else if (entry.is_regular_file()) {
                std::cout << "file: " << filenameStr << '\n';
            }
            else
                std::cout << "??    " << filenameStr << '\n';
        }
    }

        /*for (const auto& dirEntry : recursive_directory_iterator(myPath))
            std::cout << dirEntry << std::endl;*/
};
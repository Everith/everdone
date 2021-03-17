#pragma once
#include "../Core.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <time.h>

#include "../Wallpapper/wallpaper.h"

namespace file {
    std::vector<char> readFile (const std::string &filename);
    void printFile (const std::string &filename);
    void read_CSV_File (const std::string &filename);

    //void replace_line (std::string oldLine, std::string newLine, std::string filename);
};

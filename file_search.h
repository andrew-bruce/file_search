#define _GNU_SOURCE
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <filesystem>
#include <stdio.h>
#include "shlwapi.h"

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

#ifdef linux
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class FileSearch
{
    private:
    void to_lower(std::string& str);
    public:
    FileSearch() {}
    bool SearchFile(std::string search, std::string file_path);
    std::string SearchCurrentFolder(std::string search);
};
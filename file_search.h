#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <filesystem>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class FileSearch
{
    public:
    FileSearch() {}
    bool SearchFile(std::string search, std::string file_path);
    std::string SearchCurrentFolder(std::string search);
};
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>
#include <leptonica/allheaders.h>

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
    void ToLower(std::string& str);
    bool IsInTextCaseInsensitive(std::string& search, std::string& text);
    bool SearchPlanTextFile(std::string& search, std::string& file_path);
    bool SearchPdf(std::string& search, std::string& file_path);
    public:
    FileSearch() {}
    std::string SearchFolder(std::string& search, std::string& folder, bool& nameOnly, bool& contentOnly);
};
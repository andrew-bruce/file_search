#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <tesseract/baseapi.h>
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
    void to_lower(std::string& str);
    public:
    FileSearch() {}
    bool SearchFile(std::string& search, std::string& file_path);
    std::string SearchCurrentFolder(std::string& search);
    bool SearchPdf(const std::string& search, const std::string& pdfFilePath);
};
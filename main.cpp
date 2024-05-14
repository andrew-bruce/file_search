#include "file_search.h"

int main(int argc, char* argv[])
{
    std::string search;
    if (argc == 1)
    {
        std::cout << "Please provide search argument";
    }
    else
    {
        search = argv[1];
    }

    FileSearch file_searcher;

    std::string output = file_searcher.SearchCurrentFolder(search);
    std::cout << output << std::endl;

    return 0;
}
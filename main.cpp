#include "file_search.h"

int main(int argc, char* argv[])
{
    std::string search;
    std::string folder;

    if (argc == 1)
    {
        std::cout << "Must provide at least search (-s) argument, or type search ? for full instructions." << std::endl;
        return 0;
    }
    else if (argc == 2 && std::string(argv[1]) == "?")
    {
        std::string help_text = R"(Usage: my_program [options]

        Options:
        -s, --search TEXT       Specify the search text.
        -f, --folder PATH       Specify the folder to search in. If not provided, the current folder will be searched.
        -?, --help              Show this help message and exit.)";

        std::cout << help_text << std::endl;
        return 0;
    }
    else if (argc >= 2)
    {
        search = std::string(argv[1]);
    }

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-f")
        {
            folder = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-s")
        {
            search = std::string(argv[i + 1]);
        }
    }

    if (folder.empty() || folder == "")
    {
        char current_path[FILENAME_MAX];

        if (!GetCurrentDir(current_path, sizeof(current_path)))
        {
            std::cout << "Error: Could not get current directory" << std::endl;
            return 0;
        }

        folder = current_path;
    }
    else
    {
        // Check if the folder exists
        if (!std::filesystem::exists(folder) && std::filesystem::is_directory(folder))
        {
            std::cout << "Cannot find specified folder \"" << folder << "\"\n"
                << "Please check folder name and include full path" << std::endl;

        }
    }

    FileSearch file_searcher;

    std::string output = file_searcher.SearchFolder(search, folder);
    std::cout << output << std::endl;

    return 0;
}
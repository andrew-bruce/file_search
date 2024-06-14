#include "file_search.h"

int main(int argc, char* argv[])
{
    std::string search;
    std::string folder;
    bool contentOnly = false;
    bool nameOnly = false;

    if (argc == 1)
    {
        std::cout << "Must provide at least search (-s) argument, or type search ? for full instructions." << std::endl;
        return 0;
    }
    else if (argc == 2 && std::string(argv[1]) == "?")
    {
        std::string help_text = R"(Usage: search [OPTIONS] SEARCH_STRING

        Searches for files or content within files.

        Options:
        -s, --search       Perform a search (default behavior if no other option is provided)
        -n, --names        Search file names only
        -c, --content      Search file contents only
        -h, --help         Display this help message
        )";

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
        else if (std::string(argv[i]) == "-c")
        {
            contentOnly = true;
        }
        else if (std::string(argv[i]) == "-n")
        {
            nameOnly = true;
        }
    }

    if (contentOnly && nameOnly)
    {
        std::cout << "Error: Cannot specify name and content, must be one or the other, diregarding both" << std::endl;
        nameOnly = false;
        contentOnly = false;
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
        if (!std::filesystem::exists(folder) || !std::filesystem::is_directory(folder))
        {
            std::cout << "Cannot find specified folder \"" << folder << "\"\n"
                << "Please check folder name and include full path\n" << "Note that the path name is case sensitive" << std::endl;

            return 0;
        }
    }

    FileSearch file_searcher;

    std::string output = file_searcher.SearchFolder(search, folder, nameOnly, contentOnly);
    std::cout << output << std::endl;

    return 0;
}
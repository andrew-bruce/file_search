#include "file_search.h"

bool FileSearch::SearchFile(std::string search, std::string file_name)
{
    std::fstream file_reader;

    file_reader.open(file_name, std::fstream::in);

    if (file_reader.is_open())
    {
        std::string line;
        std::getline(file_reader, line);

        while (!file_reader.eof())
        {
            // size_t found = line.find(search);

            // if (found != std::string::npos)
            // {
            //     return true;
            // }

            auto pos = strcasestr(line.c_str(), search.c_str());

            if (pos != nullptr)
            {
                return true;
            }

            std::getline(file_reader, line);
        }
    }

    return false;
}

std::string FileSearch::SearchCurrentFolder(std::string search)
{
    char current_path[FILENAME_MAX];
    std::string file_names;

    if (!GetCurrentDir(current_path, sizeof(current_path)))
    {
        return "Error: Could not load current directory";
    }

    for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(current_path))
    {
        std::string file_name = dir_entry.path().string();

        if (!dir_entry.is_directory() && SearchFile(search, file_name))
        {
            file_names.append(dir_entry.path().string() + '\n');
        }
    }

    return file_names;
}

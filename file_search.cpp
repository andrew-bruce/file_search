#include "file_search.h"

bool FileSearch::SearchFile(std::string& search, std::string& file_name)
{
    std::fstream file_reader;

    file_reader.open(file_name, std::fstream::in);

    std::string ext = file_name.substr(file_name.find_last_of(".") + 1);

    if (ext == "pdf")
    {
        return SearchPdf(search, file_name);
    }

    if (file_reader.is_open())
    {
        to_lower(search);
        std::string line;
        std::getline(file_reader, line);

        while (!file_reader.eof())
        {
            to_lower(line);

            size_t found = line.find(search);

            if (found != std::string::npos)
            {
                return true;
            }

            std::getline(file_reader, line);
        }
    }

    return false;
}

std::string FileSearch::SearchCurrentFolder(std::string& search)
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

bool FileSearch::SearchPdf(const std::string& search, const std::string& pdfFilePath)
{
    // Command to execute pdftotext on the provided PDF file
    std::string command = "pdftotext " + pdfFilePath + " -";

    // Open a pipe to capture the output of the command
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        return "Error executing command.";
    }

    // Read and capture the output of the command
    std::string extractedText;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        extractedText += buffer;
    }

    // Close the pipe
    pclose(pipe);

    to_lower(extractedText);

    size_t found = extractedText.find(search);

    if (found != std::string::npos)
    {
        return true;
    }

    return false;
}


void FileSearch::to_lower(std::string& str)
{
    for (auto& ch : str)
    {
        ch = std::tolower(ch);
    }
}
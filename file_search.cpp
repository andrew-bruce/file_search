#include "file_search.h"


std::string FileSearch::SearchFolder(std::string& search, std::string& folder)
{
    std::string file_names;

    for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(folder))
    {
        std::string file_name = dir_entry.path().string();

        if (dir_entry.is_directory())
        {
            continue;
        }

        std::string ext = file_name.substr(file_name.find_last_of(".") + 1);

        if ((ext == "pdf" && SearchPdf(search, file_name)) || SearchPlanTextFile(search, file_name))
        {
            file_names.append(dir_entry.path().string() + '\n');
        }
    }

    return file_names;
}

bool FileSearch::SearchPlanTextFile(std::string& search, std::string& file_name)
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
        ToLower(search);
        std::string line;
        std::getline(file_reader, line);

        while (!file_reader.eof())
        {
            if (IsInTextCaseInsensitive(search, line))
            {
                return true;
            }

            std::getline(file_reader, line);
        }
    }

    return false;
}

bool FileSearch::SearchPdf(std::string& search, std::string& file_path)
{
    // Command to execute pdftotext on the provided PDF file
    std::string command = "pdftotext " + file_path + " -";

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
    ToLower(extractedText);

    size_t found = extractedText.find(search);

    if (IsInTextCaseInsensitive(search, extractedText))
    {
        return true;
    }

    return false;
}

bool FileSearch::IsInTextCaseInsensitive(std::string& search, std::string& text)
{
#ifdef _WIN32
    ToLower(text);

    size_t found = text.find(search);

    if (found != std::string::npos)
    {
        return true;
    }
#endif

#ifdef linux
    auto pos = strcasestr(text.c_str(), search.c_str());

    if (pos != nullptr)
    {
        return true;
    }
#endif

    return false;
}

void FileSearch::ToLower(std::string& str)
{
    for (auto& ch : str)
    {
        ch = std::tolower(ch);
    }
}
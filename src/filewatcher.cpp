#include "filewatcher.h"

#include <fstream>

#include "md5.h"

#include <filesystem>

std::string openFile(const char *filePath)
{
    std::string contents, lineBuff;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        while (getline(file, lineBuff))
        {
            contents += lineBuff + '\n';
        }
        contents.pop_back();
        file.close();
    }
    else std::__throw_runtime_error("Couldnt open file given!");
    return contents;
}

namespace ds
{
    FileWatcher::FileWatcher(const char *filePath) : filePath(filePath)
    {
        fileHash = "first run";
    }

    void FileWatcher::check()
    {
        std::string fileContents = openFile(filePath.c_str());
        std::string newHash = md5(fileContents);

        if (newHash == fileHash)
        {
            m_isChanged = false;
        }
        else
        {
            m_isChanged = true;
        }
        fileHash = newHash;
    }
} // namespace ds

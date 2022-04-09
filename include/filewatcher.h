#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <string>
#include <unordered_map>

namespace ds
{
    class FileWatcher
    {
    public:
        FileWatcher(const char *filePath);

        void check();
        bool isChanged() { return m_isChanged; }
        
        std::string filePath;
    private:
        bool m_isChanged = false;
        std::string fileHash;
    };
} // namespace ds


#endif
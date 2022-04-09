#ifndef DYNAMICMANAGER_H
#define DYNAMICMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <deque>
// todo add windows support
#include <dlfcn.h>

#include "filewatcher.h"

namespace ds
{
    struct Data
    {
        void* handle=nullptr;
        const char *srcFilePath;
    };
    
    class DynamicManager
    {
    public:
        DynamicManager();
        ~DynamicManager();

        void load(const char *srcFilePath, const char *objFilePath);
        void unload(const char *objFilePath);
        bool registerSrcAndObj(const char *srcFilePath, const char *objFilePath);
        void addIncludePath(const char *includePath);

        void* getFunction(const char *objFilePath, const char *functionName);

        std::deque<std::string>& getChanges();
        bool hasChanged(const char* file);

        void reload();
        void update();

    private:
        std::unordered_map<std::string, Data> objToData;
        std::unordered_map<std::string, std::string> srcToObj;
        std::vector<std::string> watchList;
        std::vector<FileWatcher> watchers;
        std::deque<std::string> changedQueue;
        std::vector<std::string> includes;
        
        // watcher
    };
} // namespace ds


#endif
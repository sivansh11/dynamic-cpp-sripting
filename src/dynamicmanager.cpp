#include "dynamicmanager.h"

#include <iostream>
#include <stdlib.h>

namespace ds
{
    DynamicManager::DynamicManager() {}
    DynamicManager::~DynamicManager() {}

    void DynamicManager::load(const char *srcFilePath, const char *objFilePath)
    {
        void* handle = dlopen(objFilePath, RTLD_LAZY);
        objToData[objFilePath] = {handle, srcFilePath};
        if (!handle)
        {
            std::cerr << dlerror() << '\n';
            return;
        }
    }
    bool DynamicManager::registerSrcAndObj(const char *srcFilePath, const char *objFilePath)
    {
        // loadedLibs[objFilePath] = {handle, srcFilePath};

        srcToObj[srcFilePath] = objFilePath;
        watchList.push_back(srcFilePath);
        watchers.push_back({srcFilePath});
        return true;
    }
    void DynamicManager::addIncludePath(const char *includePath)
    {
        includes.push_back({includePath});
    }


    void* DynamicManager::getFunction(const char *objFilePath, const char *functionName)
    {
        if (!objToData[objFilePath].handle)
            load(objToData[objFilePath].srcFilePath, objFilePath);
        return dlsym(objToData.at(objFilePath).handle, functionName);
    } 
    std::deque<std::string>& DynamicManager::getChanges()
    {
        return changedQueue;
    }

    bool DynamicManager::hasChanged(const char* file)
    {
        for (auto changed: changedQueue)
        {
            if (changed == file)
            {
                return true;
            }
        } 
        return false;
    }

    void DynamicManager::reload()
    {
        changedQueue.clear();
        for (auto& watcher: watchers)
        {
            watcher.check();
            if (watcher.isChanged())
            {
                changedQueue.push_back(watcher.filePath);
            }
        }
    }
    void DynamicManager::unload(const char *objFilePath)
    {
        dlclose(objToData[objFilePath].handle);
    }


    void DynamicManager::update()
    {
        for (auto& changed: changedQueue)
        {
            if (objToData[srcToObj[changed]].handle)
                unload(srcToObj[changed].c_str());
            std::cout << changed << '\n';
            std::string cmd;
            cmd += "g++ -fPIC -shared ";
            for (auto& include: includes)
            {
                cmd += "-I " + include + ' ';
            }
            cmd += changed +  " -o " + srcToObj[changed];
            // std::cout << cmd << '\n';
            std::cout << "DYNAMIC-SCRIPT::UPDATE::COMPILING_SCRIPT::" << changed << '\n';
            std::cout << cmd << '\n';
            system(cmd.c_str());
            load(changed.c_str(), srcToObj[changed].c_str());
        }
    }
} // namespace ds

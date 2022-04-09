# dynamic-cpp-sripting

add the following lines in the root cmakelists.txt to add dynamic c++ scripting support

```cmake
sub_directory(dynamic_swapper)  
target_include_directories(${PROJECT_NAME}
    dynamic_swapper
}
target_link_libraries(${PROJECT_NAME}
    dynamic_swapper
}
```

## how to use ?

first instantiate DynamicManager, then register and add includes thru

```cpp
// adds the include folder of the script
addIncludePath(const char *includePath)

// returns the address of the function
// Note: it returns a void* (so you may need to typedef your functions)
getFunction(const char *objFilePath, const char *functionName) -> void*

// registers the script src location and the respective shared obj location 
//this can be automatized thru an abstraction layer/function, done this way to not restrict anyone
registerSrcAndObj(const char *srcFilePath, const char *objFilePath)

// then every frame (ideally on a separate thread) :

// checks for changes in the registered src files, could have been named better
reload()

 // recompiles all the changed files
update()


// after reload you can 
// to get a queue of changes which will be performed in update(), ideally this is where you broadcast an event that a file has changed
getChanges() -> std::deque<std::string>
```

**NOTE**: currently linux only, Windows support is coming soon.

**NOTE**: code might change with need, the basic idea is here, some abstractions may help like auto adding src and obj files. The API may also change (only the naming, not the functionality)

If you have any suggestions, additional features that you may want, please reach out, I am open to feed back
# dynamic-cpp-sripting


add the following lines in the root cmakelists.txt to add dynamic c++ sripting support 

sub_directory(dynamic_swapper)  
target_include_directories(${PROJECT_NAME}
    dynamic_swapper
}
target_link_libraries(${PROJECT_NAME}
    dynamic_swapper
}



how to use ?
first instantiate DynamicManager


then register and add includes thru

addIncludePath(const char *includePath) (adds the include folder of the script)
registerSrcAndObj(const char *srcFilePath, const char *objFilePath) (registers the script src location and the respective shared obj location) (this can donr be automatized thru an abstraction layer/function, done this way to not restrict anyone)

now you can use 

getFunction(const char *objFilePath, const char *functionName) -> void* (returns the address of the function)
Note: it returns a void* (so you may need to typedef your functions)

then every frame (ideally on a seperate thread)

reload() (checks for changes in the registered src files, could have been named better)
update() (recompiles all the changed files)


after reload you can 
getChanges() -> std::deque<std::string> to get a queue of changes which will be performed in update(), ideally this is where you brodcast an event that a file has changed


NOTE: currently linux only, window support is coming soon.
NOTE: code might change with need, the basic idea is here, some abstractions may help like auto adding src and obj files. The API may also change (only the naming, not the functionality)


If you have any sugestions, additional features that you may want, please reach out, I am open to feedback




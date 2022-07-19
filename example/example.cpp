#include "dynamicmanager.h"

#include <thread>

typedef int (*add_t)(int, int);

int main()
{
    ds::DynamicManager dm;
    dm.registerSrcAndObj("../example/dynamically_loaded_cpp.cpp", "../example/dynamically_loaded_cpp.so");

    add_t add = (add_t)dm.getFunction("../example/dynamically_loaded_cpp.so", "add");
    int i = add(5, 6);
    std::cout << i << '\n';

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        dm.reload();
        dm.update();
        add_t add = (add_t)dm.getFunction("../example/dynamically_loaded_cpp.so", "add");
        int i = add(5, 6);
        std::cout << i << '\n';
    }
    
}
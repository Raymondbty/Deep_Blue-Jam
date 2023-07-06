#include <dlfcn.h>
#include <iostream>

int main()
{
    void* handle = dlopen("./core.so", RTLD_NOW);
    if (!handle) {
        std::cerr << "Error opening shared library: " << dlerror() << std::endl;
        return 1;
    }

    int (*main_func)() = reinterpret_cast<int (*)()>(dlsym(handle, "main"));
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Error getting symbol 'main': " << dlsym_error << std::endl;
        dlclose(handle);
        return 1;
    }

    int result = main_func();

    dlclose(handle);

    return result;
}

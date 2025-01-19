#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*plugin_func)();

void load_and_execute_plugin(const char *plugin_path, const char *func_name) {
    void *handle = dlopen(plugin_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror(); // Clear errors
    plugin_func func = (plugin_func)dlsym(handle, func_name);
    char *error = dlerror();
    if (error) {
        fprintf(stderr, "Error: %s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    func(); // Execute plugin function
    dlclose(handle);
}

int main() {
    load_and_execute_plugin("./plugin.so", "plugin_entry");
    return 0;
}

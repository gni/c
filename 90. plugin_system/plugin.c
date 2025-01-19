#include <stdio.h>

void plugin_entry() {
    printf("Hello from the plugin!\n");
}

// gcc -fPIC -shared -o plugin.so plugin.c
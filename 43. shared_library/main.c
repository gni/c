#include "shared_library.h"

int main() {
    hello_shared_library();
    return 0;
}

// gcc -fPIC -c shared_library.c
// gcc -shared -o libshared.so shared_library.o
// gcc main.c -L. -lshared -o shared_program
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
// ./shared_program

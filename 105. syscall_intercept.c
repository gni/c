#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <fcntl.h>

typedef int (*orig_open_f_type)(const char *pathname, int flags);

int open(const char *pathname, int flags, ...) {
    orig_open_f_type orig_open;
    orig_open = (orig_open_f_type)dlsym(RTLD_NEXT, "open");

    printf("Intercepted open: %s\n", pathname);

    if (flags & O_CREAT) {
        va_list args;
        va_start(args, flags);
        int mode = va_arg(args, int);
        va_end(args);
        return orig_open(pathname, flags, mode);
    } else {
        return orig_open(pathname, flags);
    }
}

// gcc -shared -fPIC -o intercept.so 105.syscall_intercept.c -ldl
// LD_PRELOAD=./intercept.so ls

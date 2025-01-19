#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void platform_sleep(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000); // Windows uses milliseconds
#else
    sleep(seconds); // POSIX uses seconds
#endif
}

int main() {
    printf("Sleeping for 2 seconds...\n");
    platform_sleep(2);
    printf("Done!\n");
    return 0;
}

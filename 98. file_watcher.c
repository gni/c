#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_SIZE (1024 * (EVENT_SIZE + 16))

int main() {
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        return 1;
    }

    int wd = inotify_add_watch(fd, ".", IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd < 0) {
        perror("inotify_add_watch");
        return 1;
    }

    printf("Watching current directory for changes...\n");
    char buffer[BUFFER_SIZE];
    while (1) {
        int length = read(fd, buffer, BUFFER_SIZE);
        if (length < 0) {
            perror("read");
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_CREATE) printf("File created: %s\n", event->name);
            if (event->mask & IN_DELETE) printf("File deleted: %s\n", event->name);
            if (event->mask & IN_MODIFY) printf("File modified: %s\n", event->name);
            i += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}

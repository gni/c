#include <stdio.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_EVENTS 5

int main() {
    int epoll_fd = epoll_create1(0);
    struct epoll_event event, events[MAX_EVENTS];

    int fd = open("test.txt", O_RDONLY | O_NONBLOCK);
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);

    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, 5000);
    printf("%d event(s) occurred.\n", num_events);

    close(fd);
    close(epoll_fd);
    return 0;
}

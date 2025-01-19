#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    message.msg_type = 1;
    strcpy(message.msg_text, "Hello, IPC Message Queue!");

    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Sent: %s\n", message.msg_text);

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Received: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL); // Destroy the queue
    return 0;
}

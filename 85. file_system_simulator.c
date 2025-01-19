#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct File {
    char name[50];
    struct File *next;
} File;

typedef struct Directory {
    char name[50];
    struct File *files;
    struct Directory *subdirs;
    struct Directory *next;
} Directory;

Directory *create_dir(const char *name) {
    Directory *dir = malloc(sizeof(Directory));
    strcpy(dir->name, name);
    dir->files = NULL;
    dir->subdirs = NULL;
    dir->next = NULL;
    return dir;
}

// Add logic for creating, listing, and deleting files and directories.

int main() {
    Directory *root = create_dir("root");
    printf("File system simulator initialized with root directory.\n");
    // Add and manipulate files/directories here.
    return 0;
}

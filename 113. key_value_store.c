#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Entry {
    char key[256];
    char value[256];
    struct Entry *next;
} Entry;

Entry *table[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

void insert(const char *key, const char *value) {
    unsigned int idx = hash(key);
    Entry *new_entry = malloc(sizeof(Entry));
    strcpy(new_entry->key, key);
    strcpy(new_entry->value, value);
    new_entry->next = table[idx];
    table[idx] = new_entry;
}

const char *get(const char *key) {
    unsigned int idx = hash(key);
    Entry *entry = table[idx];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void delete(const char *key) {
    unsigned int idx = hash(key);
    Entry *entry = table[idx];
    Entry *prev = NULL;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table[idx] = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = table[i];
        while (entry) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
}

int main() {
    insert("name", "Alice");
    insert("age", "30");
    insert("city", "Paris");

    printf("Name: %s\n", get("name"));
    printf("Age: %s\n", get("age"));

    delete("name");
    printf("Name after deletion: %s\n", get("name"));

    free_table();
    return 0;
}

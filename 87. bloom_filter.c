#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOOM_SIZE 1000
#define HASH_COUNT 3

typedef struct {
    char bit_array[BLOOM_SIZE];
} BloomFilter;

unsigned int hash1(const char *str) {
    unsigned int hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *str++;
    return hash % BLOOM_SIZE;
}

unsigned int hash2(const char *str) {
    unsigned int hash = 0;
    while (*str) hash = (hash << 7) ^ *str++;
    return hash % BLOOM_SIZE;
}

unsigned int hash3(const char *str) {
    unsigned int hash = 0;
    while (*str) hash = *str++ + (hash << 11) - hash;
    return hash % BLOOM_SIZE;
}

void add(BloomFilter *bf, const char *str) {
    bf->bit_array[hash1(str)] = 1;
    bf->bit_array[hash2(str)] = 1;
    bf->bit_array[hash3(str)] = 1;
}

int contains(BloomFilter *bf, const char *str) {
    return bf->bit_array[hash1(str)] && bf->bit_array[hash2(str)] && bf->bit_array[hash3(str)];
}

int main() {
    BloomFilter bf = {0};
    add(&bf, "hello");
    add(&bf, "world");

    printf("Contains 'hello': %d\n", contains(&bf, "hello"));
    printf("Contains 'world': %d\n", contains(&bf, "world"));
    printf("Contains 'test': %d\n", contains(&bf, "test"));
    return 0;
}

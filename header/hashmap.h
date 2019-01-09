#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct key_value_pair{
    void* key;
    void* value;
    size_t key_length;
    struct key_value_pair* next;
} key_value_pair_t;

typedef struct dictionary{
    size_t hash_map_size;
    unsigned long long current_size;
    key_value_pair_t** data;
} dictionary_t;

int hash(const char *data, size_t len);
int add_key_value_pair(dictionary_t* dict,void* key, void* value, size_t key_length);
dictionary_t *new_dictionary(size_t hash_map_size);
key_value_pair_t* get_key_value_pair(dictionary_t* dict, void* key, size_t key_length);
void remove_key_value_pair(dictionary_t* dict, void* key, size_t key_length);
void Clear(dictionary_t* to_clear);
void* get_value(dictionary_t* dict, void* key, size_t key_length);
unsigned long long get_lenght(dictionary_t* dict);

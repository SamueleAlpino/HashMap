#include <hashmap.h>

#define GET_HASH(dict,key,key_length)                                                    \
            int to_calculate_hash = hash(key, key_length);                               \
            unsigned int hash     = to_calculate_hash  % dict->hash_map_size;                \

int hash(const char *data, size_t len)
{
    int value = 0;
    size_t i;
    for (i = 0; i < len; i++)
        value += data[i];

    return value;
}

dictionary_t *new_dictionary(size_t hash_map_size)
{
    dictionary_t *new_dict = malloc(sizeof(dictionary_t));

    if (!new_dict)
        return NULL;
   
    //good optimization if size is known "a priori"
    //memset(new_dict, 0, sizeof(struct aiv_dict));
    memset(new_dict, 0, sizeof(dictionary_t));

    //useless optimization: there is a mul opcode
    //memset(new_dict->hash_map, 0, sizeof(aiv_dict_item_t *) * hash_map_size);
    new_dict->hash_map_size     = sizeof(key_value_pair_t *) * hash_map_size;
    new_dict->data              = malloc(new_dict->hash_map_size);
    new_dict->current_size      = 0;
    if (!new_dict->data)
    {
        free(new_dict);
        return NULL;
    }

    memset(new_dict->data, 0,  new_dict->hash_map_size );
    return new_dict;
}


void* get_value(dictionary_t* dict, void* key, size_t key_length)
{
    GET_HASH(dict,key,key_length);
    key_value_pair_t *current = dict->data[hash];
    while (current)
    {
        if (current->key_length == key_length && !memcmp(current->key, key, key_length))
            return current->value;
       
        current = current->next;
    }
    return NULL;
}

int add_key_value_pair(dictionary_t* dict,void* key, void* value, size_t key_length)
{
    GET_HASH(dict,key,key_length);

    key_value_pair_t* current = dict->data[hash];
    key_value_pair_t* last    = current;

    while (current)
    {
        if (current->key_length == key_length && !memcmp(current->key, key, key_length))
        {
            current->value = value;
           // dict->current_size++;
            return 0;
        }
        last    = current;
        current = current->next;
    }

    key_value_pair_t *new_key_value_pair = malloc(sizeof(key_value_pair_t));
    if (!new_key_value_pair)
        return -1;
    
    new_key_value_pair->key        = key;
    new_key_value_pair->key_length = key_length;
    new_key_value_pair->value      = value;
    new_key_value_pair->next       = NULL;

    if (last != NULL)
        last->next = new_key_value_pair;
    else
        dict->data[hash] = new_key_value_pair;

    dict->current_size++;
    
    return 0;
}

key_value_pair_t* get_key_value_pair(dictionary_t* dict, void* key, size_t key_length)
{
    GET_HASH(dict,key,key_length);

    key_value_pair_t* current = dict->data[hash];

    while(current)
    {
        if(current->key_length == key_length && !memcmp(current->key, key, key_length))
            return current;
    
        current = current->next;
    }
    return NULL;
}

void remove_key_value(dictionary_t* dict, void* key, size_t key_length)
{
    GET_HASH(dict,key,key_length);

    key_value_pair_t* current = dict->data[hash];
    key_value_pair_t* last    = current;
    while(current)
    {
        if(current->key_length == key_length && !memcmp(current->key, key, key_length))
        {
            if(!memcmp(current, last, sizeof(key_value_pair_t)) && current->next != NULL)
                dict->data[hash] = current->next;
            else if(!memcmp(current, last, sizeof(key_value_pair_t)) && current->next == NULL)
                dict->data[hash] = NULL;

            if(current->next)
                last->next = current->next;
            else
                last->next = NULL;
            
            free(current);

            memset(current, 0, sizeof(key_value_pair_t));
            dict->current_size--;
            return;
        }
        last    = current;
        current = current->next;
    }
}

unsigned long long get_lenght(dictionary_t* dict)
{
	if(dict != NULL) 
        return dict->current_size;
	else 
        return 0;
}

void clear(dictionary_t* to_clear)
{
    if(to_clear)
    {
        memset(to_clear->data, 0,  to_clear->hash_map_size );
        to_clear->current_size = 0;
        //maybe you need to set hashmapsize?
    }
}

void destroy(dictionary_t* to_destroy)              
{                                                                   
    if (to_destroy)
    {                                                        
        free(to_destroy->data);
        free(to_destroy);                           
    }                                                               
}                                                                   
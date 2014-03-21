/*
 * Hash Table 
 * by Niels Vanden Eynde 
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#ifndef NEW
#  define NEW(x) malloc(sizeof(x))
#endif

static char *
savestr(const char *str)
{
    char *save;
    size_t len;

    if (str == NULL) 
        return NULL;

    len = strlen(str);
    save = malloc(len + 1);

    if (save == NULL)
        return NULL;

    strncpy(save, str, len);
    save[len] = '\0';

    return save;
}

static unsigned int
hash(const char *string)
{
    unsigned int hashval = 0;

    while (*string != '\0')
        hashval = ((hashval << 5) + hashval) + *string++;
    return hashval;
}

static Hash_node *
HT_new_node(const char *key, void *data)
{
    Hash_node *node;

    node = NEW(Hash_node);
    node->key  = savestr(key);
    node->data = data;
    node->next = NULL;
    return node;
}

Hash_table *
HT_new(size_t size)
{
    Hash_table *table;
    
    table = NEW(Hash_table);
    if (table == NULL)
        return NULL;
    
    table->nodes = calloc(size, sizeof(Hash_node *));
    if (table->nodes == NULL) {
        free(table);
        return NULL;
    }
        
    table->size = size;
    table->count = 0;

    return table;
}

Hash_table *
HT_resize(Hash_table *table, size_t size)
{
    Hash_table *ntable;
    unsigned int i;

    ntable = HT_new(size);

    for (i = 0; i < table->size; i++) {
        Hash_node *node = table->nodes[i];
        unsigned int hashkey;
            
        if (node != NULL) {
            hash(node->key) % size;
            ntable->nodes[hashkey] = node;
        }
    }
    free(table->nodes);
    free(table);
    return ntable;
}

Hash_node *
HT_insert(Hash_table *table, const char *key, void *data)
{
    unsigned int hashkey;
    Hash_node *node;
        
    hashkey = hash(key) % table->size;
    node = table->nodes[hashkey];

    while (node != NULL && node->next != NULL) {
        if (strcmp(node->key, key) == 0) {
            free(node->data);
            node->data = data;
            return node;
        }
        node = node->next;
    }
    
    node = HT_new_node(key, data);
    node->next = table->nodes[hashkey];

    table->count++;
    table->nodes[hashkey] = node;
    return node;
}

static void
free_node(Hash_node *node)
{
    free(node->key);
    free(node);
}

void *
HT_remove(Hash_table *table, const char *key)
{
    Hash_node *node, *prev = NULL;
    unsigned int hashkey;
    void *data = NULL;

    hashkey = hash(key) % table->size;
    node = table->nodes[hashkey];

    while (node != NULL) {
        if (strcmp(node->key, key) != 0) {
            prev = node;
            node = node->next;
            continue;
        }

        if (prev != NULL)
            prev->next = node->next;
        else
            table->nodes[hashkey] = node->next;
        
        data = node->data;
        free_node(node);
        break;
    }
    return data;
}

void
HT_free(Hash_table *table)
{
    unsigned int i;
    Hash_node *node, *prev;

    for (i = 0; i < table->size; i++) {
        node = table->nodes[i];
        while (node != NULL) {
            prev = node;
            node = node->next;
            free_node(prev);
        }
    }
    
    free(table->nodes);
    free(table);
}

Hash_node *
HT_get_node(Hash_table *table, const char *key)
{
    unsigned int hashkey;
    Hash_node *node;

    if (table == NULL) 
        return NULL;

    hashkey = hash(key) % table->size;
    node = table->nodes[hashkey];

    while (node != NULL) {
        puts(node->key);
        puts(key);
        if (strcmp(node->key, key) == 0)
            return node;
        else
            node = node->next;
    }
    return NULL;
}

void *
HT_get_data(Hash_table *table, const char *key)
{
    Hash_node *node = HT_get_node(table, key);
    return (node == NULL) ? NULL : node->data;
}

 

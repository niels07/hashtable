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


#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H

typedef struct hash_node {
    char *key;                  /* Key to find a node.      */
    void *data;                 /* The data we need.        */
    struct hash_node *next;     /* Next hash in the table.  */
} Hash_node;

typedef struct hash_table {
    size_t size;                /* Size of the NODES array. */
    size_t count;               /* Number of nodes .        */
    Hash_node **nodes;          /* Array of hash nodes      */
} Hash_table;

/* Allocate a new hash table. */
extern Hash_table *HT_new(size_t /* size */);

/* Free a hash table completely. */
extern void HT_free(Hash_table * /* table */);

/* Create a new node with KEY, DATA, and 
   insert it into TABLE. */
extern Hash_node *HT_insert(Hash_table * /* table */, const char * /* key */, void * /* data */);

/* Remove a node identifier by KEY and 
   from the table and return data. */
extern void *HT_remove(Hash_table * /* table */, const char * /* key */);

/* Return a node in the table identifier
   by KEY. */ 
extern Hash_node *HT_get_node(Hash_table * /* table */, const char * /* key */);

/* Resize the table. */
extern Hash_table *HT_resize(Hash_table * /* table */, size_t /* size */);

/* Get data from the node identifier by KEY
   from TABLE. */
void *HT_get_data(Hash_table *table, const char *key);

#endif /* _HASH_TABLE_H_ */

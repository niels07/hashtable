#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

#define MAX_BUFFER 255
#define TABLE_SIZE 25

static Hash_table *table;

unsigned int 
isnum(const char *str)
{
    char *p;

    if (p == NULL || *p == '\0' || *p == '\n')
        return 0;

    for (p = (char *)str; *p != '\0'; p++) 
        if (!strchr("0123456789", *p))
            return 0;
    return 1;
}

static void
readline(const char *output, char *input)
{
    printf("%s", output);
    fgets(input, MAX_BUFFER, stdin);
    input[strlen(input) -1] = '\0';
}
    
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

void 
read_items(void)
{
    char buf[MAX_BUFFER], key[MAX_BUFFER], value[MAX_BUFFER];
    unsigned int count, i;

    for (;;) {
        readline("table items: ", buf);
        if (isnum(buf))
            break;
        else
            fprintf(stderr, "size needs to a number\n");
    }

    count = atoi(buf);
    table = HT_new(TABLE_SIZE);

    if (table == NULL) {
        fprintf(stderr, "out of memory");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < count; i++) {
        printf("node %d\n", i + 1);
        readline("  key: ", key);
        readline("  value: ", value);
        HT_insert(table, key, savestr(value));
    }
}

static void
print_items(void)
{
    char buf[MAX_BUFFER];
    char *value;

    for (;;) {
        readline("enter a key: ", buf);
        value = HT_get_data(table, buf);
        if (value == NULL) 
            printf("not found!\n");
        else
            printf("key = '%s', value = '%s'\n", buf, value);

        readline("continue? [y/n] ", buf);
        if (strcmp(buf, "y") != 0)
            break;
    }
}



int 
main(int argc, char *argv[])
{
    read_items();
    print_items();

    HT_free(table);
    return EXIT_SUCCESS;
}

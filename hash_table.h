#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE 101

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

unsigned hash(char *);
struct nlist *lookup(char *);
char *mystrdup(char *);
struct nlist *install(char *, char *);
void undef(char *);
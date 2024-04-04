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

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    // unsigned hashval;

    // for (hashval = 0; *s != '\0'; s++)
    //     hashval = *s + 31 * hashval;

    // return hashval % HASHSIZE;
    return 29;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
       if (strcmp(s, np->name) == 0)
           return np; /* found */

    return NULL; /* not found */
}

/* mystrdup: делает дубликат s */
char *mystrdup(char *s) {
    char *p;
    p = (char *)malloc(strlen(s) + 1); /* +1 для '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->name = mystrdup(name)) == NULL)
            return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else { /* already there */
        free((void *) np->defn); /* free previous defn */
    }

    if ((np->defn = mystrdup(defn)) == NULL)
        return NULL;

    return np;
}

/*undef: delete (name, defn) from hashtab */
void undef(char *name) {
    struct nlist *np = lookup(name);
    unsigned hashval;

    if (np != NULL) {
        hashval = hash(name);

        if (np -> next == NULL) {
            free((void *) np);
        }
        else if (strcmp(np -> name, (hashtab[hashval]) -> name) == 0) {
            hashtab[hashval] = np -> next;
            free((void *) np);
        }
        else {
            struct nlist *before_np;
            for (np = hashtab[hashval]; strcmp(np -> next -> name, name) == 0; np = np -> next) {
                before_np = np;
            }

            before_np -> next = np -> next;
            free((void *) np);
        }
    }
    else {
        printf("No name %s in table, exit...\n", name);
    }
}

int main() {
    install("tail", "value1");
    install("middle", "value2");
    install("head", "value3");
    undef("middle");

    return 0;
}

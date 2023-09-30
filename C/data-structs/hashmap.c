/* Generic Hash Map */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    void **keys;
    void **values;
} HashMap;

HashMap *hashCreate (int);
int hashKey(const char *);
int hashIndex(HashMap *, void *);
void hashInsert(HashMap *, void *, void *);
void *hashGet (HashMap *, void *);
void hashFree (HashMap *);

HashMap *hashCreate (const int size) {
    HashMap *h = calloc(1, sizeof (HashMap));
    h->keys = calloc(size, sizeof (void *));
    h->values = calloc(size, sizeof (void *));
    h->size = size;
    return h;
}

int hashKey(const char *string) {
    if(string == NULL) return 0;
    int res = 0;
    for(int i = 0; string[i] != '\0'; i++) 
        res += string[i];
    return res;
}

int hashIndex (HashMap *h, void *key) {
    int i = hashKey(key) % h->size;
    while (h->keys[i] && h->keys[i] != key)
        i = (i + 1) % h->size;
    return i;
}

void hashInsert (HashMap *h, void *key, void *value) {
    int i = hashIndex(h, key);
    h->keys[i] = key;
    h->values[i] = value;
}

void *hashGet (HashMap *h, void *key) {
    int i = hashIndex(h, key);
    return h->values[i];
}

void hashFree (HashMap *h) {
    free(h->values);
    free(h->keys);
    free(h);
}

int main () {
    HashMap *h = hashCreate(15);
    hashInsert(h, "hello", "world");
    hashInsert(h, "pkey", "test_of_pkey");
    printf("hello => %s\n", (char *)hashGet(h, "hello"));
    printf("pkey => %s\n", (char *)hashGet(h, "pkey"));
    hashFree(h);
    return 0;
}
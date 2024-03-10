/* Generic Hash Map */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int size;
    void **keys;
    void **values;
} HashMap;

HashMap *hashCreate (int);
int hashKey(const void *, const char *);
int hashIndex(HashMap *, void *, const char *);
void hashInsert(HashMap *, void *, void *, const char *);
void *hashGet (HashMap *, void *, const char *);
void hashFree (HashMap *);

HashMap *hashCreate (const int size) {
    HashMap *h = calloc(1, sizeof (HashMap));
    h->keys = calloc(size, sizeof (void *));
    h->values = calloc(size, sizeof (void *));
    h->size = size;
    return h;
}

/* Return the hash of the `value` of a given `valueType`.
 * Supported value types are: STRING and NUMBER */
int hashKey(const void *value, const char *valueType) {
    if(value == NULL) return 0;
    int res = 0;
    if(strcmp(valueType, "STRING") == 0) {
        char *v = (char *)value;
        for(int i = 0; v[i] != '\0'; i++) 
            res += v[i];
    } else if(strcmp(valueType, "NUMBER") == 0) {
        res = *((int *)value);
    }
    
    return res;
}

/* Return the index of an element with a certain `key`.
 * @param keyType one of the supported key types: STRING or NUMBER */
int hashIndex (HashMap *h, void *key, const char *keyType) {
    int i = hashKey(key, keyType) % h->size;
    if(strcmp(keyType, "STRING") == 0) {
        while (h->keys[i] && strcmp(h->keys[i], key) != 0)
            i = (i + 1) % h->size;
    } else if(strcmp(keyType, "NUMBER") == 0) {
        while (h->keys[i] && h->keys[i] != key)
            i = (i + 1) % h->size;
    }
    return i;
}

/* Insert a new `key` -> `value` inside the hash map `h`
 * @param keyType one of the supported key types: STRING or NUMBER */
void hashInsert (HashMap *h, void *key, void *value, const char *keyType) {
    int i = hashIndex(h, key, keyType);
    h->keys[i] = key;
    h->values[i] = value;
}

/* Search a value for a given `key` inside the hash map `h`
 * @param keyType one of the supported key types: STRING or NUMBER */
void *hashGet (HashMap *h, void *key, const char *keyType) {
    int i = hashIndex(h, key, keyType);
    return h->values[i];
}

/* Free memory pointed by the hashmap */
void hashFree (HashMap *h) {
    free(h->values);
    free(h->keys);
    free(h);
}

int main () {
    HashMap *h = hashCreate(3);
    hashInsert(h, "hello", "world", "STRING");
    hashInsert(h, "pkey", "test_of_pkey", "STRING");
    int numericKey = 34;
    hashInsert(h, &numericKey, "value_of_34", "NUMBER");
    printf("\"hello\" => %s\n", (char *)hashGet(h, "hello", "STRING"));
    printf("\"pkey\" => %s\n", (char *)hashGet(h, "pkey", "STRING"));
    printf("34 => %s\n", (char *)hashGet(h, &numericKey, "NUMBER"));
    hashFree(h);
    return 0;
}
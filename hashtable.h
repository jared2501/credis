#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct entry_s entry_t;
typedef struct hashtable_s hashtable_t;

/* Initializes a hashtable and returns a pointer to an initialized hashtable structure */
hashtable_t *create_hashtable(int size);

/* Puts the value at the key given into the hastable */
int put(hashtable_t *table, char *key, char *value);

/* Retrieves the entry at the given key, or NULL if there's none */
char *get(hashtable_t *table, char *key);

#endif /* HASHTABLE_H */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "hashtable.h"

struct entry_s {
	char *key;
	char *value;
	struct entry_s *next;
};

struct hashtable_s {
	int size;
	struct entry_s **table; /* Array of entry pointers */
};

int hash(char *key);

hashtable_t *create_hashtable(int size) {
	hashtable_t *hashtable = NULL;
	int i;

	if(size < 1) return NULL;

	/* Allocate the table itself. */
	if((hashtable = malloc(sizeof(hashtable_t ))) == NULL) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if((hashtable->table = malloc(sizeof(entry_t *) * size)) == NULL ) {
		return NULL;
	}

	for(i=0; i<size; i++) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}


int put(hashtable_t *table, char *key, char *value) {
	entry_t *new_entry = NULL;
	int hash_code;
	int bucket;
	entry_t *entry;

	/* Create new entry */
	new_entry = malloc(sizeof(entry_t));
	new_entry->key = key;
	new_entry->value = value;

	/* Determine the correct hash bucket */
	hash_code = hash(key);
	bucket = hash_code % table->size;

	/* Find the correct position to put the entry */
	entry = table->table[bucket];

	/* If there's nothing in the bucket yet, put it in there and return */
	if(entry == NULL) {
		table->table[bucket] = new_entry;
		return 0;
	}

	while(entry->next != NULL && strcmp(entry->key, key) > 0) {
		entry = entry->next;
	}

	/* Now we've stopped, we can either have the final element of the linked list of the bucket, or an element with a matching key */
	if(strcmp(entry->key, key) == 0) {
		new_entry->next = entry->next;
		free(entry);
		return 0;
	}

	entry->next = new_entry;
	return 0;
}

char *get(hashtable_t *table, char *key) {
	int hash_code;
	int bucket;
	entry_t *entry;

	hash_code = hash(key);
	bucket = hash_code % table->size;

	entry = table->table[bucket];

	if(entry == NULL) {
		return NULL;
	}

	while(entry->next != NULL) {
		if(strcmp(entry->key, key) == 0) {
			return entry->value;
		}

		entry = entry->next;
	}

	return NULL;
}

int hash(char *key) {
	unsigned long int hashval;
	int i = 0;
	int length;

	length = strlen(key);
 
	/* Convert our string to an integer */
	while(hashval<ULONG_MAX && i<length) {
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}

	return hashval;
}
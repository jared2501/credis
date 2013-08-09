#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int main(void) {
	hashtable_t *hashtable;
	char *key, *value, *output;

	key = "asdasd";
	value = "asdasd213asd";

	hashtable = create_hashtable(10);
	put(hashtable, key, value);
	output = get(hashtable, key);
	
	printf("%s\n", key);

	return 0;
}
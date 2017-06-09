#ifndef HASHMAPENTRY_H
#define	HASHMAPENTRY_H

typedef struct HashMapEntry {
	char *key;
	void *value;
	size_t size;

	struct HashMapEntry *next;
} HashMapEntry;

HashMapEntry *map_entry_new(char*, void*, size_t);
void map_entry_set(HashMapEntry*, void*, size_t);
HashMapEntry *map_entry_get(HashMapEntry*, char*);
void map_entry_append(HashMapEntry**, char*, void*, size_t);
void map_entry_free(HashMapEntry**);

#endif	/* HASHMAPENTRY_H */


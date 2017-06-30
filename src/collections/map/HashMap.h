#ifndef HASHMAP_H
#define	HASHMAP_H

#define MAP_SIZE 5
#define MAP_LOAD_FACTOR 0.9f
#define MAP_GROW_FACTOR 2.f

typedef struct HashMap {
	HashMapEntry **entries;
	float load_factor;
	float grow_factor;
	size_t slots;
	size_t size;
} HashMap;

HashMap *map_create();
HashMap *map_new(size_t, float, float);
int map_hashcode(char*);
void map_put(HashMap*, char*, void*, size_t);
void *map_get(HashMap*, char*);
void map_remove(HashMap*, char*);
void map_free(HashMap**);

#endif	/* HASHMAP_H */


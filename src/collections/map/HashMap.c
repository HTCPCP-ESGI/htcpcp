#include "../../includes.h"

HashMap *map_create(void)
{
    return map_new(MAP_SIZE, MAP_LOAD_FACTOR, MAP_GROW_FACTOR);
}

HashMap *map_new(size_t slots, float load_factor, float grow_factor)
{
	HashMap *map = (HashMap*)malloc(sizeof(HashMap));

	if(map)
	{
		map->entries = (HashMapEntry**)calloc(slots, sizeof(HashMapEntry*));
		map->slots = slots;
		map->size = 0;
		map->load_factor = load_factor;
		map->grow_factor = grow_factor;
	}

	return map;
}

void map_grow(HashMap *map)
{
	size_t i;
	int slots = map->slots * map->grow_factor;
	HashMapEntry **tmp = (HashMapEntry**)calloc(slots, sizeof(HashMapEntry*));

	// Replace the elements and free the former list memory
	for(i = 0 ; i < map->slots ; i++)
	{
		HashMapEntry *entries = map->entries[i];

		if(entries)
		{
			while(entries)
			{
				int index = map_hashcode(entries->key) % slots;
				map_entry_append(&(tmp[index]), entries->key, entries->value, entries->size);
				entries = entries->next;
			}

			map_entry_free(&entries);
		}
	}
	free(map->entries);

	// Assign new values
	map->entries = tmp;
	map->slots = slots;
}

int map_hashcode(char *key)
{
	int i, hash = 0;

	for(i = 0 ; key && *key != '\0' ; i++)
	{
		hash += *key * (i + 1);
		key++;
	}

	return hash;
}

void map_put(HashMap *map, char *key, void *value, size_t size)
{
	if(!map || !key || !value)
		return;

	int index = map_hashcode(key) % map->slots;
	HashMapEntry *entry = map_entry_get(map->entries[index], key);

	// If the key already exists, we update it
	if(entry)
		map_entry_set(entry, value, size);
	// Otherwise we simply add it
	else
	{
		// If necessary, resize the HashMap and recalculate the index
		if(map->size >= map->slots * map->load_factor)
		{
			map_grow(map);
			index = map_hashcode(key) % map->slots;
		}

		map_entry_append(&(map->entries[index]), key, value, size);
		map->size++;
	}
}

void *map_get(HashMap *map, char *key)
{
	if(!map || !key)
		return NULL;

	int index = map_hashcode(key) % map->slots;
	HashMapEntry *entry = map_entry_get(map->entries[index], key);

	if(entry)
		return entry->value;
	return NULL;
}

void map_remove(HashMap *map, char *key)
{
	if(!map || !key)
		return;

	int index = map_hashcode(key) % map->slots;
	HashMapEntry **entries = &(map->entries[index]);

	while(*entries)
	{
		if(!strcmp((*entries)->key, key))
		{
			HashMapEntry *tmp = (*entries)->next;

			free((*entries)->key);
			free((*entries)->value);
			free(*entries);

			*entries = tmp;
			map->size--;
			break;
		}

		*entries = (*entries)->next;
	}
}

HashMap *map_duplicate(HashMap *src)
{
	size_t i;
	HashMap *map = map_create();

    for(i = 0 ; i < src->slots ; i++)
    {
        HashMapEntry *attribute = src->entries[i];

        if(!attribute)
            continue;

        while(attribute)
        {
            char *value = map_get(src, attribute->key);

            // If the attribute exists, put it in the duplicate map
            if(value)
                map_put(map, attribute->key, value, strlen(value) + 1);
            // Go to next attribute
            attribute = attribute->next;
        }
    }

	return map;
}

void map_free(HashMap **map)
{
	size_t i;

	if(!map || !*map)
		return;

	for(i = 0 ; i < (*map)->slots ; i++)
		map_entry_free(&((*map)->entries[i]));

	free((*map)->entries);
	free(*map);
	*map = NULL;
}
#include "../htcpcp.h"

HashMapEntry *map_entry_new(char *key, void *value, size_t size)
{
	HashMapEntry *entry = (HashMapEntry*)malloc(sizeof(HashMapEntry));

	if(entry)
	{
		entry->key = strdup(key);
		entry->value = NULL; // Set value to NULL before calling map_entry_set
		map_entry_set(entry, value, size);
		entry->next = NULL;
	}

	return entry;
}

void map_entry_set(HashMapEntry *entry, void *value, size_t size)
{
	if(!entry || !value)
		return;

	if(entry->value)
		free(entry->value);

	entry->value = malloc(size);
	entry->size = size;
	memcpy(entry->value, value, size);
}

HashMapEntry *map_entry_get(HashMapEntry *entries, char *key)
{
	while(entries)
	{
		if(!strcmp(entries->key, key))
			return entries;

		entries = entries->next;
	}

	return NULL;
}

void map_entry_append(HashMapEntry **entries, char *key, void *value, size_t size)
{
	while(*entries)
		entries = &(*entries)->next;
	*entries = map_entry_new(key, value, size);
}

void map_entry_free(HashMapEntry **entries)
{
	if(!entries)
		return;

	while(*entries)
	{
		HashMapEntry *tmp = (*entries)->next;

		free((*entries)->key);
		free((*entries)->value);
		free(*entries);

		*entries = tmp;
	}

	*entries = NULL;
}
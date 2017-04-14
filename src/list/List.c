#include "../htcpcp.h"

List *list_new(void *value)
{
	List *list = malloc(sizeof(List));

	if(list)
	{
		list->value = value;
		list->next = NULL;
	}

	return list;
}

void list_add(List **list, void *value)
{
	while(*list)
		list = &(*list)->next;
	*list = list_new(value);
}

void *list_remove(List **list, unsigned int index)
{
    void *value = NULL;

    while(index && *list)
    {
        list = &(*list)->next;
        index--;
    }

    if(!index && *list)
    {
        List *tmp = *list;
        *list = (*list)->next;

        value = tmp->value;
        free(tmp);
    }

    return value;
}

List *list_tail(List *list)
{
	while(list && list->next)
		list = list->next;
	return list;
}

void list_free(List **list)
{
	if(!list)
		return;
	
	while(*list)
	{
		List *tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	
	*list = NULL;
}

#ifndef LIST_H
#define	LIST_H

typedef struct List {
	void *value;
	struct List *next;
} List;

List *list_new(void*);
void list_add(List**, void*);
void *list_remove(List**, unsigned int);
List *list_tail(List*);
void list_free(List**);

#endif
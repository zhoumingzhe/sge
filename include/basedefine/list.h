#ifndef BASEDEFINE_LIST_H
#define BASEDEFINE_LIST_H
#include "platform.h"
struct sge_list_entry
{
    struct sge_list_entry *prev;
    struct sge_list_entry *next;
};

sge_inline void sge_list_init(struct sge_list_entry *list)
{
    list->next = list;
    list->prev = list;
}

sge_inline void sge_list_insert_before(struct sge_list_entry *list, struct sge_list_entry *entry)
{
    entry->next = list;
    entry->prev = list->prev;
    list->prev->next = entry;
    list->prev = entry;
}

sge_inline void sge_list_insert_after(struct sge_list_entry *list, struct sge_list_entry *entry)
{
	entry->prev = list;
	entry->next = list->next;
	list->next->prev = entry;
	list->next = entry;
}

#endif
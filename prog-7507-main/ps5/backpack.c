#include "backpack.h"
#include <string.h>
#include <stdlib.h>

struct backpack *create_backpack(const int capacity)
{
	struct backpack *bpck = calloc(sizeof(struct backpack), 1);
	bpck->capacity = capacity;
	bpck->items = calloc((size_t)capacity, sizeof(struct item *));
	return bpck;
}

struct backpack *destroy_backpack(struct backpack *backpack)
{
	if (backpack == NULL)
		return NULL;

	if (backpack->items != NULL)
		destroy_containers(backpack->items);

	free(backpack);

	return NULL;
}

struct item *get_item_from_backpack(const struct backpack *backpack, char *name)
{
	if (name == NULL || backpack == NULL || strlen(name) == 0)
		return NULL;

	struct item *tm = get_from_container_by_name(backpack->items, name);

	return tm;
}

bool add_item_to_backpack(struct backpack *backpack, struct item *item)
{
	if (backpack == NULL || item == NULL || backpack->capacity == backpack->size || (item->properties != 1 && item->properties != 3 && item->properties != 5 && item->properties != 7 && item->properties != 9 && item->properties != 11))
		return false;

	if (backpack->items == NULL)
	{
		backpack->items = create_container(backpack->items, ITEM, item);
	}
	else
	{
		create_container(backpack->items, ITEM, item);
	}

	backpack->size += 1;

	return true;
}

void delete_item_from_backpack(struct backpack *backpack, struct item *item)
{
	if (backpack == NULL || item == NULL)
		return;
	else
	{
		backpack->items = remove_container(backpack->items, item);

		backpack->size -= 1;
	}
}

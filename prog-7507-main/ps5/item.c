#include "item.h"
#include <stdlib.h>
#include <string.h>

struct item *create_item(char *name, char *description, unsigned int properties)
{
	if (name == NULL || description == NULL)
		return NULL;

	size_t name_len = strlen(name);
	size_t desc_len = strlen(description);

	if (name_len == 0 || desc_len == 0)
		return NULL;

	struct item *item_ptr = malloc(sizeof(struct item));
	item_ptr->name = malloc(name_len + 1);
	item_ptr->description = malloc(desc_len + 1);
	item_ptr->properties = properties;

	if (item_ptr->name == NULL || item_ptr->description == NULL)
	{
		free(item_ptr->name);
		free(item_ptr->description);
		free(item_ptr);
		return NULL;
	}

	strncpy(item_ptr->name, name, name_len);
	item_ptr->name[name_len] = '\0';

	strncpy(item_ptr->description, description, desc_len);
	item_ptr->description[desc_len] = '\0';

	return item_ptr;
}

struct item *destroy_item(struct item *item)
{
	if (item == NULL)
		return NULL;

	free(item->name);
	free(item->description);
	free(item);

	return NULL;
}

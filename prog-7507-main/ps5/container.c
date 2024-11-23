#include "container.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct container *create_container(struct container *first, enum container_type type, void *entry)
{
	if (!entry || (first && type != first->type))
	{
		return NULL;
	}
	struct container *new_container = calloc(1, sizeof(struct container));
	new_container->type = type;
	new_container->text = entry;
	if (first)
	{
		struct container *last_container = first;
		while (last_container->next)
		{
			last_container = last_container->next;
		}
		last_container->next = new_container;
	}
	else
	{
		first = new_container;
	}
	return new_container;
}

struct container *destroy_containers(struct container *first)
{
	struct container *current_container = first;
	while (current_container)
	{
		if (current_container->type == COMMAND)
		{
			destroy_command(current_container->command);
		}
		else if (current_container->type == ITEM)
		{
			destroy_item(current_container->item);
		}
		else if (current_container->type == ROOM)
		{
			destroy_room(current_container->room);
		}
		else if (current_container->type == TEXT)
		{
			free(current_container->text);
		}
		struct container *next_container = current_container->next;
		free(current_container);
		current_container = next_container;
	}
	return NULL;
}

void *get_from_container_by_name(struct container *first, const char *name)
{
	if (!name || !first)
	{
		return NULL;
	}
	char name_lowercase[strlen(name) + 1];
	for (int i = 0; i < strlen(name) + 1; i++)
	{
		name_lowercase[i] = (char)tolower(name[i]);
	}
	struct container *current_container = first;
	while (current_container)
	{
		if (current_container->type != TEXT)
		{
			char current_name[strlen(current_container->item->name) + 1];
			for (int i = 0; i < strlen(current_container->item->name) + 1; i++)
			{
				current_name[i] = (char)tolower(current_container->item->name[i]);
			}
			int compare_result = strcmp(name_lowercase, current_name);
			if (compare_result == 0)
			{
				if (current_container->type == COMMAND)
				{
					return current_container->command;
				}
				else if (current_container->type == ITEM)
				{
					return current_container->item;
				}
				else if (current_container->type == ROOM)
				{
					return current_container->room;
				}
			}
		}
		else
		{
			char current_text[strlen(current_container->text) + 1];
			for (int i = 0; i < strlen(current_container->text) + 1; i++)
			{
				current_text[i] = (char)tolower(current_container->text[i]);
			}
			int compare_result = strcmp(name_lowercase, current_text);
			if (compare_result == 0)
			{
				return current_container->text;
			}
		}
		current_container = current_container->next;
	}
	return NULL;
}

struct container *remove_container(struct container *first, void *entry)
{
	if (entry == NULL || first == NULL)
	{
		return first;
	}
	struct container *prev = NULL;
	struct container *curr = first;
	while (curr != NULL)
	{
		switch (curr->type)
		{
		case COMMAND:
			if (memcmp(curr->command, entry, sizeof(struct command)) == 0)
			{
				if (prev == NULL)
				{
					first = curr->next;
				}
				else
				{
					prev->next = curr->next;
				}
				free(curr);
				return first;
			}
			break;
		case ITEM:
			if (memcmp(curr->item, entry, sizeof(struct item)) == 0)
			{
				if (prev == NULL)
				{
					first = curr->next;
				}
				else
				{
					prev->next = curr->next;
				}
				free(curr);
				return first;
			}
			break;
		case ROOM:
			if (memcmp(curr->room, entry, sizeof(struct room)) == 0)
			{
				if (prev == NULL)
				{
					first = curr->next;
				}
				else
				{
					prev->next = curr->next;
				}
				free(curr);
				return first;
			}
			break;
		case TEXT:
			if (strlen(curr->text) == strlen((char *)entry) && memcmp(curr->text, entry, strlen(curr->text)) == 0)
			{
				if (prev == NULL)
				{
					first = curr->next;
				}
				else
				{
					prev->next = curr->next;
				}
				free(curr);
				return first;
			}
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	return first;
}

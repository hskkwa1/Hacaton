#include "room.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct room *create_room(char *name, char *description)
{
	if (!name || !description || !strlen(name) || !strlen(description))
	{
		return NULL;
	}
	struct room *new_room = (struct room *)calloc(1, sizeof(struct room));
	new_room->name = (char *)calloc(strlen(name) + 1, sizeof(char));
	new_room->description = (char *)calloc(strlen(description) + 1, sizeof(char));
	strcpy(new_room->name, name);
	strcpy(new_room->description, description);
	return new_room;
}

struct room *destroy_room(struct room *room)
{
	if (!room)
	{
		return NULL;
	}
	free(room->name);
	free(room->description);
	destroy_containers(room->items);
	free(room);
	return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west)
{
	if (!room)
		return;

	if (north)
	{
		room->north = malloc(sizeof(struct room));
		if (!room->north)
			return;

		memcpy(room->north, north, sizeof(struct room));
	}
	else
	{
		room->north = NULL;
	}

	if (south)
	{
		room->south = malloc(sizeof(struct room));
		if (!room->south)
			return;
		
		memcpy(room->south, south, sizeof(struct room));
	}
	else
	{
		room->south = NULL;
	}

	if (east)
	{
		room->east = malloc(sizeof(struct room));
		if (!room->east)
			return;
		
		memcpy(room->east, east, sizeof(struct room));
	}
	else
	{
		room->east = NULL;
	}

	if (west)
	{
		room->west = malloc(sizeof(struct room));
		if (!room->west)
			return;
		
		memcpy(room->west, west, sizeof(struct room));
	}
	else
	{
		room->west = NULL;
	}
}

void show_room(const struct room *room)
{
	if (!room)
	{
		return;
	}
	printf("all room");
}

void delete_item_from_room(struct room *room, struct item *item)
{
	if (!room || !item)
	{
		return;
	}
	room->items = remove_container(room->items, item);
}

void add_item_to_room(struct room *room, struct item *item)
{
	if (!room || !item)
	{
		return;
	}
	if (!room->items)
	{
		room->items = create_container(NULL, ITEM, item);
	}
	else
	{
		create_container(room->items, ITEM, item);
	}
}

struct item *get_item_from_room(const struct room *room, const char *name)
{
	if (!room || !name)
	{
		return NULL;
	}
	return get_from_container_by_name(room->items, name);
}

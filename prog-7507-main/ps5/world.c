#include "world.h"
#include <stdlib.h>
#include <stdio.h>

struct container *create_world()
{
	struct room *rooms[15];
	for (int i = 0; i < 15; i++)
	{
		char name[10];
		sprintf(name, "room %d", i);
		struct room *room = create_room(name, "///");
		rooms[i] = room;
	}

	struct item *items[5];
	for (int i = 0; i < 5; i++)
	{
		char name[10];
		sprintf(name, "item %d", i + 1);
		struct item *item = create_item(name, "///", 1);
		items[i] = item;
	}

	struct container *world = add_room_to_world(NULL, rooms[0]);
	for (int i = 1; i < 15; i++)
	{
		add_room_to_world(world, rooms[i]);
		if (i == 4)
		{
			set_exits_from_room(rooms[0], rooms[1], rooms[2], rooms[3], rooms[4]);
		}
	}

	add_item_to_room(rooms[0], items[0]);
	add_item_to_room(rooms[0], items[1]);
	add_item_to_room(rooms[0], items[2]);
	add_item_to_room(rooms[1], items[3]);
	add_item_to_room(rooms[1], items[4]);

	return world;
}

struct container *add_room_to_world(struct container *world, struct room *room)
{
	if (room == NULL)
		return NULL;

	if (world == NULL)
	{
		world = create_container(NULL, ROOM, room);
		return world;
	}
	else
	{
		if (get_from_container_by_name(world, room->name) == NULL)
		{
			struct container *komnata = create_container(world, ROOM, room);
			return komnata;
		}
		else
			return NULL;
	}
}

struct container *destroy_world(struct container *world)
{
	if (world == NULL)
		return NULL;

	destroy_containers(world);

	return NULL;
}

struct room *get_room(struct container *world, char *name)
{
	if (name == NULL || world == NULL)
		return NULL;

	return get_from_container_by_name(world, name);
}

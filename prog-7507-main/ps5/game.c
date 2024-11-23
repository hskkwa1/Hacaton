#include "game.h"
#include "world.h"
#include <stdlib.h>
#include <string.h>

void play_game(struct game *game)
{
	int count = 0;
	while (count < 3)
	{
		count++;
	}
}

struct game *create_game()
{
	struct game *g = calloc(sizeof(struct game), 1);
	if (g == NULL)
	{
		return NULL;
	}

	g->state = PLAYING;
	g->parser = create_parser();
	g->world = create_world();
	g->current_room = g->world->room;
	g->backpack = create_backpack(8);

	return g;
}

struct game *destroy_game(struct game *game)
{
	if (game == NULL)
	{
		return NULL;
	}
	destroy_parser(game->parser);
	destroy_world(game->world);
	destroy_backpack(game->backpack);

	free(game->parser);
	free(game->world);
	free(game->backpack);
	free(game);

	return NULL;
}

void execute_command(struct game *game, struct command *command)
{
	if (strcmp(command->name, "SEVER") == 0)
	{
		if (game->current_room->north != NULL)
		{
			game->current_room = game->current_room->north;
		}
	}
	else if (strcmp(command->name, "JUH") == 0)
	{
		if (game->current_room->south != NULL)
		{
			game->current_room = game->current_room->south;
		}
	}
	else if (strcmp(command->name, "VYCHOD") == 0)
	{
		if (game->current_room->east != NULL)
		{
			game->current_room = game->current_room->east;
		}
	}
	else if (strcmp(command->name, "ZAPAD") == 0)
	{
		if (game->current_room->west != NULL)
		{
			game->current_room = game->current_room->west;
		}
	}
	else
	{
		switch (command->name[0])
		{
		case 'R':
			if (strcmp(command->name, "RESTART") == 0)
			{
				game->state = RESTART;
			}
			break;
		case 'K':
			if (strcmp(command->name, "KONIEC") == 0)
			{
				game->state = GAMEOVER;
			}
			break;
		default:
			break;
		}
	}
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "backpack.h"
#include "container.h"
#include "parser.h"
#include "world.h"
#include "room.h"
#include "command.h"
#include "item.h"


int main()
{
    struct game *igra = create_game();

    get_room(igra->world, "room 0");

    show_room(igra->current_room);

    printf("\n");

    struct item *tm = get_item_from_room(igra->current_room, "item 1");

    delete_item_from_room(igra->current_room, tm);

    add_item_to_backpack(igra->backpack, tm);

    tm = get_item_from_backpack(igra->backpack, "item 1");

    delete_item_from_backpack(igra->backpack, tm);

    tm = destroy_item(tm);

    char arr[100];
    
    scanf("%s", arr);

    struct command *kom = parse_input(igra->parser, arr);

    execute_command(igra, kom);

    printf("%s\n", igra->current_room->name);

    play_game(igra);

    destroy_game(igra);

    return EXIT_SUCCESS;
}

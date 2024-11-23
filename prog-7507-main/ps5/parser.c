#include "parser.h"
#include <stdlib.h>

struct parser *create_parser()
{
	struct parser *prs = malloc(sizeof(struct parser));

	if (prs == NULL)
		return NULL;

	prs->commands = create_container(prs->commands, COMMAND, create_command("VEZMI", "...", "(VEZMI)", 1));
	prs->commands = create_container(prs->commands, COMMAND, create_command("KONIEC", "...", "(KONIEC|QUIT|EXIT)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("ROZHLIADNI SA", "...", "(ROZHLIADNI SA)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("PRIKAZY", "...", "(PRIKAZY|HELP|POMOC)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("RESTART", "...", "RESTART", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("O HRE", "...", "(O HRE|ABOUT)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("POLOZ", "...", "(POLOZ)", 1));
	prs->commands = create_container(prs->commands, COMMAND, create_command("ULOZ", "...", "(SAVE|ULOZ)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("SEVER", "...", "(SEVER|S)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("JUH", "...", "(JUH|J)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("VYCHOD", "...", "(V|VYCHOD)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("ZAPAD", "...", "(Z|ZAPAD)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("VERZIA", "...", "(VERZIA)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("INVENTAR", "...", "(INVENTAR|I)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("POUZI", "...", "(POUZI)", 1));
	prs->commands = create_container(prs->commands, COMMAND, create_command("PRESKUMAJ", "...", "(PRESKUMAJ)", 0));
	prs->commands = create_container(prs->commands, COMMAND, create_command("NAHRAJ", "...", "(NAHRAJ|LOAD)", 0));

	prs->history = calloc(1, sizeof(struct container));

	if (prs->history == NULL)
	{
		destroy_parser(prs);
		return NULL;
	}

	return prs;
}

struct parser *destroy_parser(struct parser *parser)
{
	if (parser == NULL)
		return NULL;

	destroy_containers(parser->commands);

	destroy_containers(parser->history);

	free(parser);

	return NULL;
}

struct command *parse_input(struct parser *parser, char *input)
{
	if (parser == NULL || input == NULL)
		return NULL;

	struct container *f = parser->commands;

	while (f)
	{
		if (regexec(&f->command->preg, input, 0, NULL, 0) == 0)
		{
			return f->command;
		}
		f = f->next;
	}
	return NULL;
}

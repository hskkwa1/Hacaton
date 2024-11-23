#include "command.h"
#include <stdlib.h>
#include <string.h>

struct command *create_command(char *name, char *description, char *pattern, size_t nmatch)
{
	if (name == NULL || description == NULL)
		return NULL;

	if (strlen(name) == 0 || strlen(description) == 0)
		return NULL;

	struct command *crtc = calloc(sizeof(struct command), 1);

	crtc->name = calloc(strlen(name) + 1, 1);
	strcpy(crtc->name, name);

	crtc->description = calloc(strlen(description) + 1, 1);
	strcpy(crtc->description, description);

	if (pattern != NULL)
	{
		regcomp(&crtc->preg, pattern, REG_ICASE | REG_EXTENDED);
		crtc->groups = calloc(nmatch, sizeof(regmatch_t));
	}
	return crtc;
}

struct command *destroy_command(struct command *command)
{
	if (command == NULL)
		return NULL;

	regfree(&command->preg);

	free(command->groups);

	free(command->description);

	free(command->name);

	free(command);

	return NULL;
}

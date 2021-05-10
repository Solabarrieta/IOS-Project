#include "../libstring/libstring.h"

#include "character.h"

#include <stdlib.h>

void create_player(player *p, char *name)
{
    p->name = (char *)malloc(strlen(name));
    p->name = name;

    p->fails = 0;
    p->score = 0;
    p->is_dead = 0;
}
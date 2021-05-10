#include "../libstring/libstring.h"

#include "character.h"

void create_player(player *p)
{
    p->fails = 0;
    p->score = 0;
    p->is_dead = 0;
}
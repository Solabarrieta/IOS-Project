#include "../libstring/libstring.h"

#include "character.h"

void create_player(player *p)
{
    p->fails = 0;
    p->score = 0;
    p->is_dead = 0;
}

void set_name(player *p, const char *name)
{
    char *n = p->name;

    for (int i = 0; i < strlen(n); i++)
    {
        if (strlen(n) > strlen(name) && i >= strlen(name))
        {
            n[i] = ' ';
        } else {
            n[i] = name[i];
        }
    }

    n[30] = '\0';
}
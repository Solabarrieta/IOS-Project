#include "headers/exit.h"
#include "headers/menu.h"
#include "headers/cd.h"
#include "headers/clear.h"
#include "headers/signal_handler.h"
#include "headers/libstring/libstring.h"
#include "headers/characters/character.h"

#include "headers/recognizer.h"
#include "headers/executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define VILLAGE 0
#define GROVE 1
#define HAUNTED_HOUSE 2
#define FOREST_ENTRANCE 3
#define TREES_P 4
#define FOREST 5
#define EMERALD_CITY 6
#define PRAIRIE 7
#define CASTLE 8
#define GAME_OVER 9
#define RESTART 10
#define MENU 11

#define error(a)   \
    {              \
        perror(a); \
        exit(1);   \
    };

int state;

char *root_dir;
char *game_dir;

player dorothy;

int main()
{
    root_dir = getcwd((char *)NULL, 0);
    game_dir = concat(root_dir, "/config/.gamedir/village/");
    char *args[200];
    char *player_name;

    pid_t child_pid;

    state = MENU;

    args[0] = concat(root_dir, "/gsh");

    while (1)
    {
        switch (state)
        {
        case RESTART:
            create_player(&dorothy);
            state = VILLAGE;
            break;

        case MENU:
            clear_screen();
            print_menu();
            write(0, "Press ENTER to START...", 24);
            wait_until_enter();
            clear_screen();

            create_player(&dorothy);
            state = VILLAGE;

            break;

        case VILLAGE:
            clear_screen();
            println(concat(ANSI_COLOR_YELLOW, bold("CHAPTER 1: <<VILLAGE>>")));
            write(0, "Press enter to continue...\n", 28);
            wait_until_enter();

            cd(game_dir);
            read_doc("village");

            if (execute(1, args))
            {
                dorothy.fails++;
            }
            else
            {
                speak_character(GLINDA, "Oh! Good, did you have fun with those commands? I guess you had, my dear.");
                speak_character(GLINDA, "But now its time to save OS from my sis.");
                speak_character(GLINDA, "Quick! We don't so much time!");
            }

            write(1, "Press enter to continue...\n", 28);
            wait_until_enter();

            state = GROVE;
            break;

        case GROVE:
            clear_screen();
            println(concat(ANSI_COLOR_YELLOW, bold("CHAPTER 2: <<THE GROVE>>")));
            write(0, "Press enter to continue...\n", 28);
            wait_until_enter();

            read_doc("grove/grove");

            if (execute(1, args))
            {
                dorothy.fails++;
            }

            break;

        case HAUNTED_HOUSE:
            cd(concat(game_dir, "grove/.haunted_house/"));
            break;

        case FOREST_ENTRANCE:
            cd(concat(game_dir, "grove/forest_entrance/"));
            break;

        case TREES_P:
            cd(concat(game_dir, "grove/forest_entrance/.trees/"));
            break;

        case FOREST:
            cd(concat(game_dir, "grove/forest_entrance/forest/"));
            break;

        case EMERALD_CITY:
            cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/"));
            break;

        case PRAIRIE:
            cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/"));
            break;

        case CASTLE:
            cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/castle"));
            break;

        case GAME_OVER:
            if (dorothy.is_dead)
            {
                // TODO: something when dorothy dies...
            }
            else
            {
                // Exit properly. If Ctrl+c, exit sin respesto. Else, con respeto por ganar el juego.
            }
            break;
        }
    }
    return 0;
}
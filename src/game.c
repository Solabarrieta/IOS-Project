#include "headers/exit.h"
#include "headers/menu.h"
#include "headers/cd.h"
#include "headers/clear.h"
#include "headers/signal_handler.h"
#include "headers/libstring/libstring.h"
#include "headers/characters/character.h"

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
int fails;
char *root_dir;
char *game_dir;

void wait_until_enter()
{
    do
    {

    } while (getchar() != 10);
}

int read_doc(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *buff;

    while (read(fd, buff, 1) == 1)
    {
        if (*buff == '_')
        {
            write(1, "PLAYER", 7);
        }
        else
        {
            write(1, buff, 1);

            if (*buff == '.' || *buff == '!' || *buff == '?')
            {
                write(1, "\n", 1);
                wait_until_enter();
            }
        }
    }

    close(fd);

    println("");

    return 0;
}

int execute(char *argv[])
{
    int status;
    pid_t child_pid = fork();

    switch (child_pid)
    {
    case -1:
        return 1;

    case 0:
        // Child process
        execvp(argv[0], argv);
        break;

    default:
        // Parent process.
        wait(&status);
        return WIFEXITED(status) > 0 ? 1 : 0;
    }

    return 0;
}

int main()
{
    char *glinda = GLINDA;
    char *ofelia = OFELIA;
    char *scarecrown = SCARECROWN;

    root_dir = getcwd((char *)NULL, 0);
    game_dir = concat(root_dir, "/config/.gamedir/village/");
    char *current_dir;
    char *args[200];

    pid_t child_pid;

    state = MENU;

    args[0] = concat(root_dir, "/gsh");

    while (1)
    {
        switch (state)
        {
        case RESTART:
            fails = 0;
            state = VILLAGE;
            break;

        case MENU:
            clear_screen();
            print_menu();
            write(0, "Press ENTER to START...", 24);
            wait_until_enter();
            clear_screen();

            fails = 0;
            state = VILLAGE;

            break;

        case VILLAGE:
            clear_screen();
            println(concat(ANSI_COLOR_YELLOW, bold("CHAPTER 1: <<VILLAGE>>")));
            write(0, "Press enter to continue...\n", 28);
            wait_until_enter();

            cd(game_dir);
            read_doc("village");

            speak_character(glinda, "I recommend you to ask for HELP in this new utility to my sisters!");
            speak_character(glinda, "We'll see in the grove, near someone who's speacial for me.");
            speak_character(glinda, "Remember the command <<exit>> in order to exit this game, honey :) Have FUN!");

            cd(root_dir);
            fails += execute(args);
            cd(game_dir);

            if (fails == 1)
            {
                // TODO: read Ofelia's phrases from a file...
                speak_character(ofelia, "As I suspect you are not good enough for this world. This is the first warning, be careful because Your little lovely Dog would die if you make another mistake.");
            }
            else
            {
                speak_character(glinda, "Oh! Good, did you have fun with those commands? I guess you had, my dear.");
                speak_character(glinda, "But now its time to save OS from my sis.");
                speak_character(glinda, "Quick! We don't so much time!");
            }

            println("");
            write(0, "Press enter to continue...\n", 28);
            wait_until_enter();

            state = GROVE;

            break;

        case GROVE:
            clear_screen();
            println(concat(ANSI_COLOR_YELLOW, bold("CHAPTER 2: <<THE GROVE>>")));
            write(0, "Press enter to continue...\n", 28);
            wait_until_enter();

            cd(concat(game_dir, "/grove/"));
            read_doc("grove");

            speak_character(scarecrown, "I don't know where are we. Can you help us?");
            speak_character(scarecrown, "I think you could use <<pwd>>. The Good Witch told me.");

            cd(root_dir);
            fails += execute(args);
            cd(game_dir);

            break;

        case HAUNTED_HOUSE:
            cd(concat(game_dir, "/grove/.haunted_house/"));
            break;

        case FOREST_ENTRANCE:
            cd(concat(game_dir, "/grove/forest_entrance/"));
            break;

        case TREES_P:
            cd(concat(game_dir, "/grove/forest_entrance/.trees/"));
            break;

        case FOREST:
            cd(concat(game_dir, "/grove/forest_entrance/forest/"));
            break;

        case EMERALD_CITY:
            cd(concat(game_dir, "/grove/forest_entrance/forest/emerald_city/"));
            break;

        case PRAIRIE:
            cd(concat(game_dir, "/grove/forest_entrance/forest/emerald_city/prairie/"));
            break;

        case CASTLE:
            cd(concat(game_dir, "/grove/forest_entrance/forest/emerald_city/prairie/castle"));
            break;

        case GAME_OVER:

            break;

        default:
            break;
        }
    }
    return 0;
}
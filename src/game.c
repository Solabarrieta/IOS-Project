/**
 * @file game.c
 * @author The Wizard of OS Team - TEAM 2.2
 * @brief The Wizard of OS GAME !!!
 * @version 0.1
 * @date 2021-05-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Commands used later, in the game.
#include "headers/exit.h"
#include "headers/menu.h"
#include "headers/cd.h"
#include "headers/clear.h"

// Headers for signal execution.
#include "headers/signal_handler.h"
#include "headers/libstring/libstring.h"
#include "headers/characters/character.h"
#include "headers/recognizer.h"
#include "headers/executor.h"

// Standard libraries and syscall managing.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <math.h>

#define error(a)   \
    {              \
        perror(a); \
        exit(1);   \
    };

/* STATES of the GAME */

#define RESTART 0
#define MENU 1

#define VILLAGE 2
#define GROVE 3

#define HAUNTED_HOUSE 4

#define FOREST_ENTRANCE 5
#define TREES_P 6
#define FOREST 7
#define EMERALD_CITY 8
#define PRAIRIE 9
#define CASTLE 10

#define GAME_OVER 11

/* STATES of the GAME */

/* CHAPTERS TITLE */

#define VILLAGE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 1: <<THE VILLAGE>>"))
#define GROVE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 2: <<THE GROVE>>"))
#define HAUNTED_HOUSE_TIT concat(ANSI_COLOR_CYAN, bold("CHAPTER 2b: <<THE HAUNTED HOUSE>>"))
#define FOREST_ENTRANCE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 3: <<THE FOREST ENTRANCE>>"))
#define TREES_P_TIT concat(ANSI_COLOR_CYAN, bold("CHAPTER 3b: <<THE TREES>>"))
#define FOREST_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 4: <<THE FOREST>>"))
#define EMERALD_CITY_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 5: <<EMERALD CITY>>"))
#define PRAIRIE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 6: <<THE PRAIRIE>>"))
#define CASTLE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 7: <<THE CASTLE>>"))

/* CHAPTERS TITLE */

// The number of seconds to sleep on loading screens.
static float loading_screen = 0.2;

// The number of seconds to sleep before changing the character's line.
static float loading_line = 2;

void loading(int wt_val)
{
    int perct;
    char snum[5];

    for (int i = 0; i < wt_val; i++)
    {
        switch (i % 4)
        {
        case 1:
            print("\r/ ");
            break;

        case 2:
            print("\r- ");
            break;

        case 3:
            print("\r\\ ");
            break;

        default:
            print("\r- ");
            break;
        }

        perct = (int)ceil(((float)100 * i) / wt_val);

        sprintf(snum, "%d%%", perct);
        print(snum);
        usleep(loading_screen * 1000000);
    }
}

int main()
{
    // Random seed, for random number obtention. SET to computer time.
    srand(time(NULL));

    // State of the game
    static int state = MENU;

    // Player struct, for statistics and name saving.
    player dorothy;
    char player_name[31];

    // '/' and gamedir defined, for the game. '/' ~ to the root of the filesystem of the game, and important reference for the game.
    char *root_dir = getcwd((char *)NULL, 0);
    char *game_dir = concat(root_dir, "/config/.gamedir/village/");

    // ARGS for commands.
    char *args[200];

    while (1)
    {
        switch (state)
        {
        case RESTART:
            clear_screen();
            printerr(THE_SYSTEM, "Restarting the player... Resurrecting her.");
            sleep(5);

            printerr(THE_SYSTEM, "Poor little girl :(");
            sleep(loading_line);

            println("She looks like if a trail passed over her a hundred times.");
            sleep(loading_line);

            println(concat(concat("That ", OFELIA), " must be a monster..."));
            sleep(loading_line);

            create_player(&dorothy);

            loading(256);

            println("\nWell, it is done!");
            sleep(loading_line);

            println("You can now play again against that witch and save OS, if you want.");
            sleep(loading_line);

            println("Else, you already know which are the ways to exit OS, don't you?");
            sleep(loading_line);

            state = VILLAGE;
            wait_until_enter();

            break;

        case MENU:
            clear_screen();

            // Print the menu screen and wait until enter is pressed
            print_menu();
            print("Press ENTER to START... ");
            wait_until_enter();
            println("Loading... ");
            loading(128);
            println("\n\tDONE!");
            println("Press ENTER key to continue...");
            wait_until_enter();

            clear_screen();

            create_player(&dorothy);
            state = VILLAGE;

            break;

        case VILLAGE:
            // Save player name
            speak_character(GLINDA, "Whats you name, dear?");
            scanf("%s", player_name);
            set_name(&dorothy, player_name);
            println("Saving, please wait... ");
            loading(16);
            println("\nDONE!");

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            // Go to VILLAGE
            println(VILLAGE_TIT);
            println("\rPress ENTER key to continue...");
            wait_until_enter();

            cd(game_dir);
            read_doc("village.txt");

            args[0] = (char *)malloc(strlen(root_dir) + strlen("/gsh"));
            strcpy(args[0], root_dir);
            strcat(args[0], "/gsh");

            cd(root_dir);

            if (execute(1, args))
            {
                dorothy.fails++;
            }
            else
            {
                print("\r");
                speak_character(GLINDA, "Oh! Good, did you have fun with those commands? I guess you had, my dear.");
                print("\r");
                speak_character(GLINDA, "But now its time to save OS from my sis.");
                print("\r");
                speak_character(GLINDA, "Quick! We don't so much time!");
            }

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = GROVE;

            break;

        case GROVE:
            clear_screen();
            println(GROVE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            read_doc("grove/grove");

            if (execute(1, args))
            {
                dorothy.fails++;
            }

            state = HAUNTED_HOUSE;

            break;

        case HAUNTED_HOUSE:
            // cd(concat(game_dir, "grove/.haunted_house/"));

            clear_screen();
            println(HAUNTED_HOUSE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = FOREST_ENTRANCE;
            break;

        case FOREST_ENTRANCE:
            // cd(concat(game_dir, "grove/forest_entrance/"));

            clear_screen();
            println(FOREST_ENTRANCE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = TREES_P;
            break;

        case TREES_P:
            // cd(concat(game_dir, "grove/forest_entrance/.trees/"));

            clear_screen();
            println(TREES_P_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = FOREST;
            break;

        case FOREST:
            // cd(concat(game_dir, "grove/forest_entrance/forest/"));

            clear_screen();
            println(FOREST_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = EMERALD_CITY;
            break;

        case EMERALD_CITY:
            // cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/"));

            clear_screen();
            println(EMERALD_CITY_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = PRAIRIE;
            break;

        case PRAIRIE:
            // cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/"));

            clear_screen();
            println(PRAIRIE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = CASTLE;
            break;

        case CASTLE:
            // cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/castle"));

            clear_screen();
            println(CASTLE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            state = GAME_OVER;
            break;

        case GAME_OVER:
            clear_screen();

            println("THE END!");

            if (dorothy.is_dead)
            {
                speak_character(GLINDA, "Oh, no... Here we go again.");

                switch (rand() % 5)
                {
                case 1:
                    println("Why?! Why did you have to fail so many times?!");
                    break;

                case 2:
                    println("Oh my godness! Are you serious? How could anyone fail so many time with such simple spells?");
                    break;

                case 3:
                    println("You, hideous ape...");
                    break;

                case 4:
                    println("I'm bored of players.");
                    println("I think I should play with androids, like others...");
                    println("They are more interesting than apes pushing buttons...");
                    break;

                default:
                    println("Could you please be kinder with the computer?");
                    println("Some day, you will break it if you fail so many time.");
                    println("So I will.");
                    break;
                }

                state = MENU;
                // state = RESTART;
            }
            else
            {
                speak_character(GLINDA, "Thank you, dear, for playing this wonderful game!");
                println("I think the world is now a better place.");
                state = MENU;
            }

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            break;
        }
    }
    return 0;
}
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

#define RESTART -1
#define MENU -2
#define GAME_OVER -3

#define VILLAGE 1
#define GROVE 2

#define HAUNTED_HOUSE 21
#define BASEMENT 211
#define BATHROOM 212
#define BEDROOM 213
#define KITCHEN 214
#define LIVINGROOM 215

#define FOREST_ENTRANCE 3

#define TREES_P 31

#define FOREST 4
#define EMERALD_CITY 5
#define PRAIRIE 6
#define CASTLE 7

/* STATES of the GAME */

/* CHAPTERS, SECTIONS TITLE */

#define VILLAGE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 1: <<THE VILLAGE>>"))
#define GROVE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 2: <<THE GROVE>>"))

#define HAUNTED_HOUSE_TIT concat(ANSI_COLOR_CYAN, bold("CHAPTER 2b: <<THE HAUNTED HOUSE>>"))
#define BASEMENT_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The basement")
#define BATHROOM_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The bathroom")
#define BEDROOM_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The bedroom")
#define KITCHEN_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The kitchen")
#define LIVINGROOM_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The livingroom")

#define FOREST_ENTRANCE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 3: <<THE FOREST ENTRANCE>>"))
#define TREES_P_TIT concat(ANSI_COLOR_CYAN, bold("CHAPTER 3b: <<THE TREES>>"))
#define FOREST_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 4: <<THE FOREST>>"))
#define EMERALD_CITY_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 5: <<EMERALD CITY>>"))
#define PRAIRIE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 6: <<THE PRAIRIE>>"))
#define CASTLE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 7: <<THE CASTLE>>"))

/* CHAPTERS, SECTIONS TITLE */

// The number of seconds to sleep on loading screens.
static float loading_screen = 0.2;

// The number of seconds to sleep before changing the character's line.
static float loading_line = 2;

void loading(int wt_val)
{
    int perct;
    char snum[5];

    for (int i = 0; i <= wt_val; i++)
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
    char player_name[31], read_buff, *args[200];

    // '/' and gamedir defined, for the game. '/' ~ to the root of the filesystem of the game, and important reference for the game.
    char *root_dir = getcwd((char *)NULL, 0);
    char *game_dir = concat(root_dir, "/config/.gamedir/village/");
    char *current_dir;

    char election[20];

    int argc;

    args[2] = root_dir;

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
            // Print the menu screen and wait until enter is pressed.
            clear_screen();
            print_menu();
            print("Press ENTER to START... ");
            wait_until_enter();

            // Then, load the game.
            println("\nGreetings PLAYER!");
            sleep(loading_line);
            print("My name is ");
            print(GLINDA);
            println(" and I am the protector of this realm.");
            sleep(loading_line);
            speak_character(GLINDA, "I need you help to save OS from its threats, because only the player has ability to stop the evil of my sister but, first, ");
            sleep(loading_line);
            println("Whats you name, dear?");
            print("Please, here my sweet child >> ");
            scanf("%s", player_name);
            set_name(&dorothy, player_name);
            println(concat("Greetings, ", player_name));
            sleep(loading_line);
            println("Saving, please wait... ");
            loading(16);
            println(" DONE!");
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            println("Loading... ");
            // loading(128);
            loading(32);
            println(" DONE!");
            println("Press ENTER key to continue...");
            wait_until_enter();

            create_player(&dorothy);
            state = VILLAGE;

            break;

        case VILLAGE:
            // HERE begins the true game!
            clear_screen();
            println(VILLAGE_TIT);
            println("\rPress ENTER key to continue...");
            wait_until_enter();

            // GOTO The Village, and set the text to be read.
            // There, GLIDA will explain the game to THE PLAYER,
            // and OFELIA, The Most Evil Witch Ever, will warn Dorothy about
            // introducing commands wrong.
            cd(game_dir);
            current_dir = game_dir;

            // The first introduction!
            read_doc("village.txt", player_name);

            // Once the text is read, the user is encouraged to look for help
            // in the terminal.
            args[0] = (char *)malloc(strlen(root_dir) + strlen("/gsh"));
            strcpy(args[0], root_dir);
            strcat(args[0], "/gsh");

            args[1] = current_dir;
            argc = 3;

            if (execute(argc, args))
            {
                println("");
                read_doc(concat(root_dir, "/config/.mob/badwitch_first.txt"), player_name);
                dorothy.fails++;
            }

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
            // The player arrives to the GROVE
            clear_screen();
            println(GROVE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd("grove/");

            current_dir = concat(current_dir, "grove/");
            args[1] = current_dir;

            // And the Scarecrow appears!
            read_doc("grove.txt", player_name);

            if (execute(argc, args))
            {
                println("");
                read_doc(concat(root_dir, "/config/.mob/badwitch_second.txt"), player_name);
                dorothy.fails++;
            }

            println(concat(concat("Hello! I am ", JASMINE), ", and I will help you to use your player-magic during the game! Ask me for HELP if you don't exactly know how to spell some spell correctly!!! Don't be shy :)"));
            sleep(loading_line);
            speak_character(JASMINE, concat(concat("Where do you wanna go, ", player_name), " ? The HAUNTED HOUSE or The FOREST ENTRANCE"));
            sleep(loading_line);
            speak_character(JASMINE, "The HAUNTED HOUSE is not in the YELLOW path :)), and it is option to choose it. You can come back anytime!");
            sleep(loading_line);
            print("Remember, you choose: ");
            scanf("%[^\n]%*c", election);

            if (!strcmp(to_lowercase(election), "haunted house") || !strcmp(to_lowercase(election), "the haunted house")) {
                speak_character(JASMINE, "Here we go!! Tight your laces, darling, this is gonna be so much fun!!");
                println("<< TELEPORTING magic sounds >>");
                state = HAUNTED_HOUSE;
            } else if (!strcmp(to_lowercase(election), "forest entrance") || !strcmp(to_lowercase(election), "the forest entrance")) {
                speak_character(JASMINE, "OK, I would be delighted to help you anytime you ask me :)");
                state = FOREST_ENTRANCE;
            }

            println("\rPress ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            break;

        case HAUNTED_HOUSE:
            // If the user chooses it, she can enter the haunted house...
            clear_screen();
            println(HAUNTED_HOUSE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            // Entering the mansion, uhhh...
            cd(".haunted_house/");
            read_doc("haunted_house_init.txt", player_name);


            println("\rPress ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = FOREST_ENTRANCE;

            break;

        case FOREST_ENTRANCE:
            // cd(concat(game_dir, "grove/forest_entrance/"));

            clear_screen();
            println(FOREST_ENTRANCE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = TREES_P;

            break;

        case TREES_P:
            // cd(concat(game_dir, "grove/forest_entrance/.trees/"));

            clear_screen();
            println(TREES_P_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = FOREST;

            break;

        case FOREST:
            // cd(concat(game_dir, "grove/forest_entrance/forest/"));

            clear_screen();
            println(FOREST_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = EMERALD_CITY;

            break;

        case EMERALD_CITY:
            // cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/"));

            clear_screen();
            println(EMERALD_CITY_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = PRAIRIE;

            break;

        case PRAIRIE:
            // cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/"));

            clear_screen();
            println(PRAIRIE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

            state = CASTLE;

            break;

        case CASTLE:
            // cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/castle"));

            clear_screen();
            println(CASTLE_TIT);

            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(game_dir);

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            println("Saving, please wait... ");
            loading(32);
            println("\nDONE!");
            println("Press ENTER key to continue...");

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

                state = RESTART;
            }
            else
            {
                speak_character(GLINDA, "Thank you, dear, for playing this wonderful game!");
                println("I think the world is now a better place.");
                state = MENU;

                // If exit, close offlia
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
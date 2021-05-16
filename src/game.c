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
#include "headers/cd.h"
#include "headers/clear.h"

// Headers for signal execution.
#include "headers/signal_handler.h"
#include "headers/libstring/libstring.h"
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
static float loading_line = 0.8 * 1000000;

// Medium saving rate...
static float saving_time = 0.11;

/* DOROTHY */
// Where is she?
static int state = MENU;
// Other statistics
static int fails = 0;
static int deaths = 0;

void print_fails(int fails, char *root_dir)
{
    switch (fails)
    {
    case 1:
        read_doc(concat(root_dir, "/config/.mob/badwitch_first.txt"));
        break;

    case 2:
        read_doc(concat(root_dir, "/config/.mob/badwitch_second.txt"));
        break;

    case 3:
        read_doc(concat(root_dir, "/config/.mob/badwitch_last.txt"));
        break;

    default:
        println("No FAILS!");
        break;
    }
}

void loading(int wt_val)
{
    int perct;
    char ch, snum[22];

    for (int i = 0; i <= wt_val; i++)
    {
        switch (i % 4)
        {
        case 1:
            ch = '/';
            break;

        case 3:
            ch = '\\';
            break;

        default:
            ch = '-';
            break;
        }

        perct = (int)ceil(((float)100 * i) / wt_val);

        sprintf(snum, "\rLoading... %c%d%%", ch, perct);
        print(snum);
        usleep(loading_screen * 1000000);
    }

    println(" DONE!");
    println("Press ENTER key to continue...");
    wait_until_enter();
}

void save()
{
    static int wt_val = 32;

    int perct;
    char ch, snum[42];

    println("Press ENTER key to continue...");
    wait_until_enter();

    for (int i = 0; i <= wt_val; i++)
    {
        switch (i % 4)
        {
        case 1:
            ch = '/';
            break;

        case 3:
            ch = '\\';
            break;

        default:
            ch = '-';
            break;
        }

        perct = (int)ceil(((float)100 * i) / wt_val);

        sprintf(snum, "\rSaving progress, please wait... %c%d%%", ch, perct);
        print(snum);
        usleep(saving_time * 1000000);
    }

    println(" DONE!");
    println("Press ENTER key to continue...");
    wait_until_enter();
}

int main()
{
    // Random seed, for random number obtention. SET to computer time.
    srand(time(NULL));
    
    // DOROTHY
    char player_name[31];

    // How many time has Dorothy accessed one place?
    int times_access;

    // For choosing.
    char election[20];

    // '/' and gamedir defined, for the game. '/' ~ to the root of the filesystem of the game, and important reference for the game.
    char *args[200];
    int argc;

    char *root_dir = getcwd((char *)NULL, 0);
    char *game_dir = concat(root_dir, "/config/.gamedir/village/");

    while (1)
    {
        switch (state)
        {
        case RESTART:
            clear_screen();
            printerr(THE_SYSTEM, "Resurrecting the player...");
            loading(32);

            printerr(THE_SYSTEM, "Poor little girl :(");
            usleep(loading_line);
            println("She looks like if a trail passed over her a hundred times.");
            usleep(loading_line);
            println(concat(concat("That ", OFELIA), " must be a monster..."));
            usleep(loading_line);

            loading(256);

            println("You can now play again against that witch and save OS, if you want.");
            usleep(loading_line);

            println("Else, you already know which are the ways to exit OS, don't you?");
            usleep(loading_line);

            wait_until_enter();

            fails = 0;
            state = VILLAGE;

            break;

        case MENU:
            clear_screen();
            println("***************************************************************");
            println("***************************************************************");
            println("***************************************************************");
            println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
            println("**************|******* THE WIZARD OF OS *******|***************");
            println("**************|                                |***************");
            println("**************|**** \"A wizardry adventure\" ****|***************");
            println("**************|                                |***************");
            println("**************|  \"Hurry up! Toto is waiting!\"  |***************");
            println("**************|                                |***************");
            println("**************|*** Press enter key to begin ***|***************");
            println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
            println("***************************************************************");
            println("***************************************************************");
            println("***************************************************************");
            print("Press ENTER to START... ");
            wait_until_enter();

            // Then, load the game. Do it by means of text.
            println("\nGreetings PLAYER!");
            usleep(loading_line);
            print("My name is ");
            print(GLINDA);
            println(" and I am the protector of this realm.");
            usleep(loading_line);
            speak_character(GLINDA, "I need your help to save OS from its threats!");
            println("because only the player has the ability to stop the evil of my sister but,");
            usleep(loading_line);

            // Set the name!
            print("first, whats you name, dear? ");
            scanf("%s", player_name);
            print("\n");

            // Great the player for registering.
            println(concat("Greetings, ", concat(player_name, ".")));
            println("I'm glad to meet you... I hope you help is enough to stop my sister...");
            usleep(loading_line);

            save();
            clear_screen();

            // loading(128);
            loading(32);

            fails = 0;
            state = VILLAGE;
            break;

        case VILLAGE:
            clear_screen();
            println(VILLAGE_TIT);
            println("\rPress ENTER key to continue...");
            wait_until_enter();

            cd(game_dir);

            // The introduction
            read_doc("village.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (execute(argc, args))
            {
                println("");
                print_fails(++fails, root_dir);
            }

            save();
            state = GROVE;
            break;

        case GROVE:
            // The player arrives to the GROVE
            clear_screen();
            println(GROVE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd("grove/");
            read_doc("grove.txt");

            // Terminal
            args[0] = (char *)malloc(strlen(root_dir) + 5);
            strcpy(args[0], root_dir);
            strcat(args[0], "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (execute(argc, args))
            {
                println("");
                print_fails(++fails, root_dir);
            }

            // JASMINE's text!
            println(concat(concat("Hello! I am ", JASMINE), ", and I will help you to use your player-magic during the game! Ask me for HELP if you don't exactly know how to spell some spell correctly!!! Don't be shy :)"));
            usleep(loading_line);
            speak_character(JASMINE, concat(concat("Where do you wanna go, ", player_name), "? The HAUNTED HOUSE or The FOREST ENTRANCE (default) ?"));
            usleep(loading_line);
            speak_character(JASMINE, "The HAUNTED HOUSE is not in the YELLOW path :)), and it is option to choose it. You can come back anytime!");
            usleep(loading_line);
            print("Remember, you choose: ");

            fflush(stdin);
            // This character sequence allows to read whitespaces inside lines
            scanf("%[^\n]%*c", election);
            fflush(stdin);

            if (!strcmp(to_lowercase(election), "haunted house") || !strcmp(to_lowercase(election), "the haunted house"))
            {
                speak_character(JASMINE, "Here we go!! Tight your laces, darling, this is gonna be so much fun!!");
                println("<< TELEPORTING magic sounds >>");

                state = HAUNTED_HOUSE;
            }
            else if (!strcmp(to_lowercase(election), "forest entrance") || !strcmp(to_lowercase(election), "the forest entrance"))
            {
                speak_character(JASMINE, "OK, I would be delighted to help you anytime you ask me :)");
                state = FOREST_ENTRANCE;
            }
            else
            {
                state = FOREST_ENTRANCE;
            }

            times_access = 0;
            save();
            break;

        case HAUNTED_HOUSE:
            /* OPTIONAL */

            clear_screen();
            println(HAUNTED_HOUSE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(".haunted_house");

            if (!times_access)
            {
                // Entering the mansion, uhhh...
                read_doc("haunted_house_init.txt");
                wait_until_enter();
            }

            times_access++;

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            // Access to other places :)
            state = execute(argc, args);

            // Exit the mansion...
            if (state <= 1)
            {
                read_doc("haunted_house_end.txt");

                times_access = 0;
                save();
                state = FOREST_ENTRANCE;
            }

            /* OPTIONAL */
            break;

        case BEDROOM:
            clear_screen();
            println(BEDROOM_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("bedroom/");

            read_doc("haunted_house_bedroom.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (!execute(argc, args))
            {
                state = HAUNTED_HOUSE;
            }
            else
            {
                print_fails(++fails, root_dir);
            }

            break;

        case KITCHEN:
            clear_screen();
            println(KITCHEN_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("kitchen/");

            read_doc("haunted_house_kitchen.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (!execute(argc, args))
            {
                state = HAUNTED_HOUSE;
            }
            else
            {
                print_fails(++fails, root_dir);
            }

            break;

        case LIVINGROOM:
            clear_screen();
            println(LIVINGROOM_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("livingroom/");

            read_doc("haunted_house_livingroom.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (!execute(argc, args))
            {
                state = HAUNTED_HOUSE;
            }
            else
            {
                print_fails(++fails, root_dir);
            }

            break;

        case BATHROOM:
            clear_screen();
            println(BATHROOM_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("bathroom/");

            read_doc("haunted_house_bathroom.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (!execute(argc, args))
            {
                state = HAUNTED_HOUSE;
            }
            else
            {
                print_fails(++fails, root_dir);
            }

            break;

        case BASEMENT:
            clear_screen();
            println(BASEMENT_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("basement");

            read_doc("haunted_house_basement.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            if (!execute(argc, args))
            {
                state = HAUNTED_HOUSE;
            }
            else
            {
                print_fails(++fails, root_dir);
            }

            break;

        case FOREST_ENTRANCE:
            // The player follows the yellow path and arrives to the forest entrances, where the tinman is
            clear_screen();
            println(FOREST_ENTRANCE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("forest_entrance");
            read_doc("forest_entrance.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            save();
            state = TREES_P;
            break;

        case TREES_P:
            clear_screen();
            println(TREES_P_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(".trees");
            read_doc("tree.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            save();
            state = FOREST;
            break;

        case FOREST:
            clear_screen();
            println(FOREST_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("forest");

            read_doc("forest.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            save();
            state = EMERALD_CITY;
            break;

        case EMERALD_CITY:
            clear_screen();
            println(EMERALD_CITY_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("emerald_city");
            read_doc("emerald_city.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            save();
            state = PRAIRIE;
            break;

        case PRAIRIE:
            clear_screen();
            println(PRAIRIE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("prairie");
            read_doc("prairie.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            save();
            state = CASTLE;
            break;

        case CASTLE:
            clear_screen();
            println(CASTLE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd("castle");
            read_doc("castle.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;

            save();
            state = GAME_OVER;
            break;

        case GAME_OVER:
            clear_screen();

            println("THE END!");

            /* Dorothy is death iff has failes three times */
            if (fails != 0 && fails % 3 == 0 && deaths > 0)
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
            }

            print("\r");
            println("Press ENTER key to continue...");
            wait_until_enter();

            save();

            break;
        }
    }

    return 0;
}
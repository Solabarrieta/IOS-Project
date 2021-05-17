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

#include "headers/game.h"

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

        case 2:
            ch = '|';
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

        case 2:
            ch = '|';
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
    clear_screen();
}

static int state = MENU, fails = 0, deaths = 0;

int main()
{
    // Random seed, for random number obtention. SET to computer time.
    srand(time(NULL));

    // How many time has Dorothy accessed one place?
    int times_access, argc;

    // For choosing.
    char std, election[20], player_name[31], *args[200];

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
            save();
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

            // loading(128);
            loading(32);

            fails = 0;
            state = VILLAGE;
            clear_screen();
            break;

        case VILLAGE:
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

            state = GROVE;
            save();
            break;

        case GROVE:
            println(GROVE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/"));
            read_doc("grove.txt");

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
            println(HAUNTED_HOUSE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();
            clear_screen();

            cd(concat(game_dir, "grove/.haunted_house/"));

            if (!times_access)
            {
                read_doc("haunted_house_init.txt");
                wait_until_enter();
            }

            times_access++;

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

            // Exit the mansion...
            if (state <= 1)
            {
                read_doc("haunted_house_end.txt");

                times_access = 0;
                state = FOREST_ENTRANCE;
                save();
            }
            else
            {
                clear_screen();
            }

            break;

        case BEDROOM:
            println(BEDROOM_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/.haunted_house/bedroom/"));
            read_doc("haunted_house_bedroom.txt");

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
            else
            {
                state = HAUNTED_HOUSE;
            }

            clear_screen();
            break;

        case KITCHEN:
            println(KITCHEN_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/.haunted_house/kitchen/"));
            read_doc("haunted_house_kitchen.txt");

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
            else
            {
                state = HAUNTED_HOUSE;
            }

            clear_screen();
            break;

        case LIVINGROOM:
            println(LIVINGROOM_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/.haunted_house/livingroom/"));
            read_doc("haunted_house_livingroom.txt");

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
            else
            {
                state = HAUNTED_HOUSE;
            }

            clear_screen();
            break;

        case BATHROOM:
            println(BATHROOM_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/.haunted_house/bathroom/"));
            read_doc("haunted_house_bathroom.txt");

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
            else
            {
                state = HAUNTED_HOUSE;
            }

            clear_screen();
            break;

        case BASEMENT:
            println(BASEMENT_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/.haunted_house/basement/"));
            read_doc("haunted_house_basement.txt");

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
            else
            {
                state = HAUNTED_HOUSE;
            }

            clear_screen();
            break;

        case FOREST_ENTRANCE:
            println(FOREST_ENTRANCE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/forest_entrance/"));
            read_doc("forest_entrance.txt");

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

            state = TREES_P;
            save();
            break;

        case TREES_P:
            println(TREES_P_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/forest_entrance/.trees/"));
            read_doc("tree.txt");

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

            state = FOREST;
            save();
            break;

        case FOREST:
            println(FOREST_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/forest_entrance/forest/"));
            read_doc("forest.txt");

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

            state = EMERALD_CITY;
            save();
            break;

        case EMERALD_CITY:
            println(EMERALD_CITY_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/"));
            read_doc("emerald_city.txt");

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

            state = PRAIRIE;
            save();
            break;

        case PRAIRIE:
            println(PRAIRIE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/"));
            read_doc("prairie.txt");

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

            state = CASTLE;
            save();
            break;

        case CASTLE:
            println(CASTLE_TIT);
            println("Press ENTER key to continue...");
            wait_until_enter();

            cd(concat(game_dir, "grove/forest_entrance/forest/emerald_city/prairie/castle/"));
            read_doc("castle.txt");

            // Terminal
            args[0] = concat(root_dir, "/gsh");
            args[1] = getcwd((char *)NULL, 0);
            args[2] = root_dir;
            argc = 3;
            execute(argc, args);

            state = GAME_OVER;
            save();
            break;

        case GAME_OVER:
            println("THE END!");

            /* Dorothy is death iff has failes three times */
            if (fails == 3)
            {
                if (deaths == 0)
                {
                    speak_character(GLINDA, "Oh, no... Poor little player...");
                }
                else
                {
                    speak_character(GLINDA, "Oh, no... Here we go again.");
                }

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

                deaths++;
                state = RESTART;
            }
            else
            {
                speak_character(GLINDA, "Thank you, dear, for playing this wonderful game!");
                println("I think the world is now a better place.");
                state = MENU;
            }

            save();
            break;
        }
    }

    return 0;
}
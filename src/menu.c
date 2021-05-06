/**
 * @file menu.c
 * @author David Cuenca, Team 2.2
 * @brief Menu file, for The Wizard Of OS.
 * @version 0.1
 * @date 2021-05-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "headers/libstring/libstring.h"

#define MAXLINE 200

/**
* @brief The menu screen!
*/
void print_menu()
{
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
}

/**
 * @brief The options menu!
 * @param selected_option The selected option, as an integer.
 */
void print_menu_options(int selected_option)
{
    switch (selected_option)
    {
    case 1:
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("**************|                                 |***************");
        println("**************|   MENU:                         |***************");
        println("**************| >> 1.  PLAY GAME                |***************");
        println("**************|    2.  SCORE LIST               |***************");
        println("**************|                                 |***************");
        println("**************|    3.  EXIT GAME                |***************");
        println("**************|                                 |***************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        break;

    case 2:
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("**************|                                 |***************");
        println("**************|   MENU:                         |***************");
        println("**************|    1.  PLAY GAME                |***************");
        println("**************| >> 2.  SCORE LIST               |***************");
        println("**************|                                 |***************");
        println("**************|    3.  EXIT GAME                |***************");
        println("**************|                                 |***************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        break;

    case 3:
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("**************|                                 |***************");
        println("**************|   MENU:                         |***************");
        println("**************|    1.  PLAY GAME                |***************");
        println("**************|    2.  SCORE LIST               |***************");
        println("**************|                                 |***************");
        println("**************| >> 3.  EXIT GAME                |***************");
        println("**************|                                 |***************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        break;

    case 0:
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("**************|                                 |***************");
        println("**************|   MENU:                         |***************");
        println("**************|    1.  PLAY GAME                |***************");
        println("**************|    2.  SCORE LIST               |***************");
        println("**************|                                 |***************");
        println("**************|    3.  EXIT GAME                |***************");
        println("**************|                                 |***************");
        println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
        println("****************************************************************");
        println("****************************************************************");
        println("****************************************************************");
        break;
    }
}
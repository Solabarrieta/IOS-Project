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

#include "headers/menu.h"

void restore_terminal(struct termios *saved_glindos)
{
    tcsetattr(STDIN_FILENO, TCSANOW, saved_glindos);
}

void clear_screen()
{
    for (u16 rows = 0; rows < MAXLINE; rows++)
    {
        println("");
    }
}

void print_menu()
{
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
}

void print_menu_options(u8 selected_option)
{
    clear_screen();
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
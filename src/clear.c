/**
 * @file clear.c
 * @author David Cuenca Marcos
 * @brief Clear the screen.
 * @version 0.1
 * @date 2021-05-06
 * 
 * @copyright Copyright (c) 2021
 */

#include <unistd.h>

#define MAXLINE 200

void clear_screen()
{
    int rows;

    for (rows = 0; rows < MAXLINE; rows++)
    {
        write(1, "\n", 1);
    }
}
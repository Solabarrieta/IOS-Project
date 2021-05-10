/**
 * @file touch.c
 * @author Mikel Aristu
 *
 * @brief The command used to create items.
 *
 * @version 0.3
 * @date 2021-03-24
 *
 * @copyright Copyright (c) 2021
 */

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
* @brief This void method will call to the open function. In case of error, the open system call will return -1 and an error message will appear.
*
* @param f_name that will be the wanted file name to be created.
* @return int 1 iff failure.
*/
int touch(char *f_name)
{
    int fd = open(f_name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        printerr("Oh no! I cannot create that tool!", THE_SYSTEM);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printerr("Oh no, you hit your hand while you where making that tool. You should revise it before it gets worse.", THE_SYSTEM);
        return 1;
    }

    return touch(argv[1]);
}

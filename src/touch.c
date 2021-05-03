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

#include "headers/touch.h"

int touch(char *f_name)
{
    char *err_title = THE_SYSTEM;

    // S_IWUSR: 00400 user has write permission
    // S_IRUSR: 00400 user has read permission.
    // S_IRGRP: 00040 group has read permission.
    // S_IROTH: 00004 others have read permission.
    int fd = open(f_name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        printerr("Oh no! I cannot create that tool!", err_title);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *err_title = THE_SYSTEM;

    if (argc != 2) {
        printerr("Oh no, you hit your hand while you where making that tool. You should revise it before it gets worse.", err_title);
        _exit(EXIT_FAILURE);
    }

    _exit(touch(argv[1]) ? EXIT_FAILURE : EXIT_SUCCESS);
}

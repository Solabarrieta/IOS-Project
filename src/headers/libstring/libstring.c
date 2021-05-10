/**
 * @file string.c
 * @author David Cuenca Marcos
 * @brief Modified string library implementation.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include "libstring.h"

#include <stdlib.h>
#include <unistd.h>

char *concat(char *str1, char *str2)
{
    char *r_string = (char *)malloc(strlen(str1) + strlen(str2));
    strcpy(r_string, str1);
    strcat(r_string, str2);
    return r_string;
}

void print(char *str)
{
    ssize_t buff;
    buff = write(1, str, strlen(str));
}

void println(char *str)
{
    print(concat(str, "\n"));
}

void printerr(char *str, char *err_title)
{
    char *result = concat(concat(concat(err_title, ": "), str), "\n");
    ssize_t buff = write(2, result, strlen(result));
}

char *bold(char *str)
{
    return concat(concat(BOLD, str), ANSI_RESET);
}

char *underlined(char *str)
{
    return concat(concat(UNDERLINE, str), ANSI_RESET);
}

char *reversed(char *str)
{
    return concat(concat(REVERSE, str), ANSI_RESET);
}
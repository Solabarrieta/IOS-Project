/**
 * @file string.h
 * @author David Cuenca Marcos
 * @brief Modified string library header.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include <string.h>

// COLORS in ANSI, for Terminal coloring
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"
// BOLD text
#define BOLD "\x1b[1m"
// UNDERLINE text
#define UNDERLINE "\x1b[4m"
// REVERSE background, text color
#define REVERSE "\x1b[7m"
// RESET
#define ANSI_RESET "\x1b[0m"

#define THE_SYSTEM "\x1b[4m\x1b[7m\x1b[31mTHE SYSTEM\x1b[0m"
#define PLAYER "\x1b[4m\x1b[37m\x1b[1mPLAYER\x1b[0m"
#define GLINDA "\x1b[4m\x1b[1m\x1b[36mGlinda, <<The Good Witch of the NORTH>>\x1b[0m"
#define OFELIA "\x1b[4m\x1b[1m\x1b[31mOfelia, <<The Most Evil Bad Witch, The Witch of the WEST>>\x1b[0m"
#define GERTRUDIS "\x1b[4m\x1b[1m\x1b[33mGertrudis, <<The Evil Witch of the EAST>>\x1b[0m"
#define JASMINE "\x1b[4m\x1b[1m\x1b[32mJasmine, <<The Good Witch of the SOUTH>>\x1b[0m"
#define SCARECROWN "\x1b[4m\x1b[1mThe Brainless Scarecrown\x1b[0m"
#define TINMAN "\x1b[4m\x1b[1mThe Heartless Tinman\x1b[0m"
#define LION "\x1b[4m\x1b[1mThe Coward Lion\x1b[0m"
#define DOG "\x1b[4m\x1b[1mTOTO <<My doge>>\x1b[0m"
#define TREES "\x1b[4m\x1b[1mForest trees\x1b[0m"
#define GUARDIAN "\x1b[4m\x1b[1mGuardian\x1b[0m"
#define GHOST "\x1b[4m\x1b[1mCASPER <<The Friendly Ghost>>\x1b[0m"
#define ADMIN "\x1b[4m\x1b[1mTHE ADMIN\x1b[0m"

#define speak_character(character, text) println(concat(character, concat(": ", text)));

/**
 * @brief Concat two string.
 * 
 * @param str1 First str to concat.
 * @param str2 Second str to concat.
 * @return char str1 + str2.
 */
extern char *concat(char *str1, char *str2);

/**
 * @brief Print a string, without an ending char implicit.
 * 
 * @param str String to print.
 */
extern void print(char *str);

/**
 * @brief Print a string, with an implicit \n at the end of the string.
 * 
 * @param str String to print.
 */
extern void println(char *str);

/**
 * @brief Print an error message.
 * 
 * @param str Error msg.
 * @param err_title The character that advises the player about the error.
 */
extern void printerr(char *err_title, char *str);

/**
 * @brief Set a string as bold text.
 * 
 * @param str The text to bold.
 * @return char* The text "bolded".
 */
extern char *bold(char *str);

/**
 * @brief Set a string as underlined.
 * 
 * @param str The text to underline.
 * @return char* The text underlined.
 */
extern char *underline(char *str);

/**
 * @brief Set a text reversed.
 * 
 * @param str The text, to reverse in color.
 * @return char* The text, reversed in color.
 */
extern char *reverse(char *str);

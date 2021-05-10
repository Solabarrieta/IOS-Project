/* SYSTEM definition, for error messages inside the game (for the player) */
#define THE_SYSTEM underlined(reversed(concat(ANSI_COLOR_RED, "THE SYSTEM")));

// The player
#define PLAYER underlined(concat(ANSI_COLOR_WHITE, bold("The Player")));

// Definition of THE WITCHES
// The four witches' titles
#define GLINDA_NAME "Glinda"
#define GLINDA_TITLE ", <<The Good Witch of the NORTH>>"
#define GLINDA_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_CYAN, concat(GLINDA_NAME, GLINDA_TITLE))))
#define GLINDA GLINDA_COMPLETE
#define SHORT_GLINDA concat(BOLD, underlined(concat(ANSI_COLOR_CYAN, GLINDA_NAME)))

#define OFELIA_NAME "Ofelia"
#define OFELIA_TITLE ", <<The Most Evil Bad Witch, The Witch of the WEST>>"
#define OFELIA_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_RED, concat(OFELIA_NAME, OFELIA_TITLE))))
#define OFELIA OFELIA_COMPLETE
#define SHORT_OFELIA concat(BOLD, underlined(concat(ANSI_COLOR_RED, concat(OFELIA_NAME, ", <<The Most Evil Bad Witch>>"))))

#define GERTRUDIS_NAME "Gertrudis"
#define GERTRUDIS_TITLE ", <<The Evil Witch of the EAST>>"
#define GERTRUDIS_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_YELLOW, concat(GERTRUDIS_NAME, GERTRUDIS_TITLE))))
#define GERTRUDIS GERTRUDIS_COMPLETE
#define SHORT_GERTRUDIS concat(BOLD, underlined(concat(ANSI_COLOR_YELLOW, GERTRUDIS_NAME)))

#define JASMINE_NAME "Jasmine"
#define JASMINE_TITLE ", <<The Good Witch of the SOUTH>>"
#define JASMINE_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_GREEN, concat(JASMINE_NAME, JASMINE_TITLE))))
#define JASMINE JASMINE_COMPLETE
#define SHORT_JASMINE concat(BOLD, underlined(concat(ANSI_COLOR_GREEN, GERTRUDIS_NAME)))

/* Definition of the COMPANIONS */
// The Three Knights of the Player + DOG
#define SCARECROWN underlined(bold("The Brainless Scarecrown"))
#define TINMAN underlined(bold("The Heartless Tinman"))
#define LION underlined(bold("The Coward Lion"))

// This is Toto, you fellow dog :DD
#define DOG concat(BOLD, underlined("TOTO <<My doge>>"))

/* Definition of EXTRAS */
#define TREES concat(BOLD, underlined("Forest trees"))
#define GUARDIAN concat(BOLD, underlined("Guardian"))
#define GHOST concat(BOLD, underlined("CASPER <<The Friendly Ghost>>"))
#define ADMIN concat(BOLD, underlined("THE ADMIN"))

#define speak_character(character, text)                \
    {                                                   \
        println(concat(character, concat(": ", text))); \
    };

typedef struct
{
    char *name;
    unsigned char is_dead;
    unsigned char fails;
    unsigned int score;
} player;

/**
 * @brief Create a player object.
 * 
 * @param p The player.
 * @param name The name of the player.
 */
extern void create_player(player *p, char *name);
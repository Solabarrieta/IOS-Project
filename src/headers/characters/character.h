#define THE_SYSTEM  "\x1b[4m\x1b[7m\x1b[31mTHE SYSTEM\x1b[0m"
#define PLAYER      "\x1b[4m\x1b[37m\x1b[1mPLAYER\x1b[0m"
#define GLINDA      "\x1b[4m\x1b[1m\x1b[36mGlinda, <<The Good Witch of the NORTH>>\x1b[0m"
#define OFELIA      "\x1b[4m\x1b[1m\x1b[31mOfelia, <<The Most Evil Bad Witch, The Witch of the WEST>>\x1b[0m"
#define GERTRUDIS   "\x1b[4m\x1b[1m\x1b[33mGertrudis, <<The Evil Witch of the EAST>>\x1b[0m"
#define JASMINE     "\x1b[4m\x1b[1m\x1b[32mJasmine, <<The Good Witch of the SOUTH>>\x1b[0m"
#define SCARECROWN  "\x1b[4m\x1b[1mThe Brainless Scarecrown\x1b[0m"
#define TINMAN      "\x1b[4m\x1b[1mThe Heartless Tinman\x1b[0m"
#define LION        "\x1b[4m\x1b[1mThe Coward Lion\x1b[0m"
#define DOG         "\x1b[4m\x1b[1mTOTO <<My doge>>\x1b[0m"
#define TREES       "\x1b[4m\x1b[1mForest trees\x1b[0m"
#define GUARDIAN    "\x1b[4m\x1b[1mGuardian\x1b[0m"
#define GHOST       "\x1b[4m\x1b[1mCASPER <<The Friendly Ghost>>\x1b[0m"
#define ADMIN       "\x1b[4m\x1b[1mTHE ADMIN\x1b[0m"

#define speak_character(character, text)                \
    {                                                   \
        println(concat(character, concat(": ", text))); \
    };

typedef struct player
{
    char name[31];
    unsigned char is_dead;
    unsigned char fails;
    unsigned int score;
} player;

/**
 * @brief Create a player object.
 * 
 * @param p The player.
 */
extern void create_player(player *p);

/**
 * @brief Set the name of the player.
 * 
 * @param p The player.
 * @param name Her name.
 */
extern void set_name(player *p, const char *name);
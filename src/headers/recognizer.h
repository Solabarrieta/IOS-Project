/**
 * @brief Wait.
 * 
 */
extern void wait_until_enter();

/**
 * @brief Returns the lowecase form of a word.
 * 
 * @param word The word to transform.
 * @return char* The lowercase form of a word.
 */
char *to_lowercase(char *word);

/**
 * @brief Recognizes uppercase words.
 * 
 * @param word The word.
 * @return int 1 iff uppercase.
 */
int is_uppercase(char *word);

/**
 * @brief Returns if a char is command.
 * 
 * @param cmd The possible command.
 * @return int 1 iff command.
 */
int is_command(char *cmd);

/**
 * @brief Recognizer program.
 * 
 * @param filename The file to recognize.
 * @param player_name The name of the player to be shown on screen.
 * @return int 0 iff successful.
 */
extern int read_doc(char *filename, char *player_name);
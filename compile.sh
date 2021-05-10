#!/bin/bash
#!/bin/zsh

# SCRIPT FOR COMPILING ALL THE DEPENDENCES THE PROGRAM WILL NEED.
# CREATION
# BY DAVID CUENCA MARCOS, 30/03/2021.
# CHANGESLOG
# MOD. David Cuenca Marcos, 14/04/2021.
# MOD. David Cuenca Marcos, 28/04/2021: ALL flag, for complete compilation; .version saving, for later, next compilations,
# in other Linux flavours, Windows.

# true iff Compile everything, as an argument.
ALL="$1"

last_vers="$(uname -r)"
vers=$last_vers

echo "Current OS: $vers"
echo "Current location: $(pwd)"

if [[ !(-s .version) ]]; then
    echo $vers > .version
else
    last_vers="$(cat .version)"

    if [[ $vers != $last_vers ]]; then
        echo "Different OS than before. Recompiling."
        echo "Last time: $last_vers"
    fi
fi

# Compile libstring
if [[ $ALL == "true" || $last_vers != $vers || -n "$(git diff src/headers/libstring/libstring.c)" || -n "$(git diff src/headers/libstring/libstring.h)" ]]; then
    echo "Compile libstring."
    gcc -c -fpic src/headers/libstring/libstring.c -o build/libstring.o
    gcc -shared build/libstring.o -o build/libstring.so 
    sudo cp build/libstring.so /usr/lib
    sudo chmod 0755 /usr/lib/libstring.so
fi

sudo ldconfig

############### COMMAND COMPILATION PROCESS ###############
echo "**PRE-COMPILATION**"
# Precompiling characters
if [[ $ALL == "true" || $last_vers != $vers || !(-s shell) || -n "$(git diff src/headers/characters/character.c)" || -n "$(git diff src/headers/characters/character.h)" ]]; then
    echo "Precompiling characters..."
    gcc -c src/headers/characters/character.c -o build/characters.o
fi

echo "**COMPILATION**"

# Compile CAT command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cat) || -n "$(git diff src/cat.c)" ]]; then
    echo "Compile cat."
    gcc src/cat.c build/characters.o -o bin/cat -lstring
fi

# Compile CP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cp) || -n "$(git diff src/cp.c)" ]]; then
    echo "Compile cp."
    gcc src/cp.c -o bin/cp -lstring
fi

# Compile GREP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/grep) || -n "$(git diff src/grep.c)" ]]; then
    echo "Compile grep."
    gcc src/grep.c -o bin/grep -lstring
fi

# Compile HELP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/help) || -n "$(git diff src/help.c)" ]]; then
    echo "Compile help."
    gcc src/help.c build/characters.o -o bin/help -lstring
fi

# Compile LS command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/ls) || -n "$(git diff src/ls.c)" ]]; then
    echo "Compile ls."
    gcc src/ls.c build/characters.o -o bin/ls -lstring
fi

# Compile MV command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/mv) || -n "$(git diff src/mv.c)" ]]; then
    echo "Compile mv."
    gcc src/mv.c build/characters.o -o bin/mv -lstring
fi

# Compile PWD command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/pwd) || -n "$(git diff src/pwd.c)" ]]; then
    echo "Compile pwd."
    gcc src/pwd.c build/characters.o -o bin/pwd -lstring
fi

# Compile STEE command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/stee) || -n "$(git diff src/stee.c)" ]]; then
    echo "Compile stee."
    gcc src/stee.c build/characters.o -o bin/stee -lstring
fi

# Compile TOUCH command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/touch) || -n "$(git diff src/touch.c)" ]]; then
    echo "Compile touch."
    gcc src/touch.c build/characters.o -o bin/touch -lstring
fi

# Compile MAN command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/man) || -n "$(git diff src/man.c)" ]]; then
    echo "Compile man."
    gcc src/man.c build/characters.o -o bin/man -lstring
fi

############### COMMAND COMPILATION PROCESS ###############

# COMPILE SHELL.
if [[ $ALL == "true" || $last_vers != $vers || !(-s gsh) || -n "$(git diff src/shell.c)" ]]; then
    echo "COMPILING SHELL"
    gcc src/shell.c src/cd.c src/exit.c src/signal_handler.c src/clear.c src/menu.c src/executor.c src/headers/characters/character.c -o gsh -lstring
fi

if [[ $ALL == "true" || $last_vers != $vers || !(-s game) || -n "$(git diff src/game.c)" ]]; then
    echo "COMPILING GAME FILE"
    gcc src/game.c src/exit.c src/signal_handler.c src/clear.c src/menu.c src/recognizer.c src/executor.c src/cd.c src/headers/characters/character.c -o TWOS_Game -lstring
fi

if [[ $last_vers != $vers ]]; then
    echo $vers > .version
fi

echo "**END of Compilation**"

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

# Checking if the OS before was different from the current one
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
    gcc -c -fPIC src/headers/libstring/libstring.c -o build/libstring.o
    gcc -shared build/libstring.so build/libstring.o
fi

# Add the library to the path
export LD_LIBRARY_PATH="build/libstring.so":$LD_LIBRARY_PATH
STRING="build/"

############### COMMAND COMPILATION PROCESS ###############
echo "**COMPILATION**"

# Compile CAT command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cat) || -n "$(git diff src/cat.c)" ]]; then
    echo "Compile cat."
    gcc src/cat.c -L$STRING -lstring -o bin/cat
fi

# Compile CP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cp) || -n "$(git diff src/cp.c)" ]]; then
    echo "Compile cp."
    gcc src/cp.c -L$STRING -lstring -o bin/cp
fi

# Compile GREP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/grep) || -n "$(git diff src/grep.c)" ]]; then
    echo "Compile grep."
    gcc src/grep.c -L$STRING -lstring -o bin/grep
fi

# Compile HELP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/help) || -n "$(git diff src/help.c)" ]]; then
    echo "Compile help."
    gcc src/help.c -L$STRING -lstring -o bin/help
fi

# Compile LS command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/ls) || -n "$(git diff src/ls.c)" ]]; then
    echo "Compile ls."
    gcc src/ls.c -L$STRING -lstring -o bin/ls
fi

# Compile MV command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/mv) || -n "$(git diff src/mv.c)" ]]; then
    echo "Compile mv."
    gcc src/mv.c -L$STRING -lstring -o bin/mv
fi

# Compile PWD command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/pwd) || -n "$(git diff src/pwd.c)" ]]; then
    echo "Compile pwd."
    gcc src/pwd.c -L$STRING -lstring -o bin/pwd
fi

# Compile STEE command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/stee) || -n "$(git diff src/stee.c)" ]]; then
    echo "Compile stee."
    gcc src/stee.c -L$STRING -lstring -o bin/stee
fi

# Compile TOUCH command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/touch) || -n "$(git diff src/touch.c)" ]]; then
    echo "Compile touch."
    gcc src/touch.c -L$STRING -lstring -o bin/touch
fi

# Compile MAN command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/man) || -n "$(git diff src/man.c)" ]]; then
    echo "Compile man."
    gcc src/man.c src/recognizer.c -L$STRING -lstring -lm -o bin/man
fi

############### COMMAND COMPILATION PROCESS ###############

# COMPILE SHELL.
if [[ $ALL == "true" || $last_vers != $vers || !(-s gsh) || -n "$(git diff src/shell.c)" ]]; then
    echo "COMPILING SHELL"
    gcc src/shell.c src/cd.c src/exit.c src/signal_handler.c src/clear.c src/executor.c -o gsh -L$STRING -lstring
fi

if [[ $ALL == "true" || $last_vers != $vers || !(-s game) || -n "$(git diff src/game.c)" ]]; then
    echo "COMPILING GAME FILE"
    
    if [[ "$1" == "debug" ]]; then
        echo "DEBUG mode"
        gcc src/game.c src/exit.c src/signal_handler.c src/clear.c src/recognizer.c src/executor.c src/cd.c -o TWOS_Game -L$STRING -lstring -lm --debug
    else
        gcc src/game.c src/exit.c src/signal_handler.c src/clear.c src/recognizer.c src/executor.c src/cd.c -o TWOS_Game -L$STRING -lstring -lm
    fi
fi

if [[ $last_vers != $vers ]]; then
    echo $vers > .version
fi

echo "**END of Compilation**"

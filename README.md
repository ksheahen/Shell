# Shell Project

For my CSCE 3600 class, I developed a shell in C that replicates core shell functionalities. This shell supports interactive command execution as well as reading commands from bath files. It parses user input, allowing for proper command execution for commands with (or without) I/O redirection and/or piping. It also supports a couple of built-in command functions (e.g. cd, exit).

## Features

- Interactive Mode
- Batch Mode
- Built-in Commands
- Prompt/Looping
- Parsing
- Command history

## Work-In Progress

- Built-in path command
    - display current pathname list
    - append one pathname
    - remove one pathname
    - e.g path, path + ./bin, path - ./bin
- Built-in myhistory command
    - ~lists shell history of previous commands~
    - ~flag -c to clear history~
    - flag -e number to execute the command at number in the list
- Built-in alias command
    - allows user to create a shortcut for commands
- Support signal handling and terminal controle
- Customization
    - customize prompt
    - color change

## Known Bugs

- Piping and redirection has outdated code and is broken. Needs to be updated to working state.

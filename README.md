This project has been created as part of the 42 curriculum by cde-la-r & adpedrer.

# Minishell

## Description

Minishell is a minimalist command-line interpreter created for the 42 school curriculum. The objective is to write a functional shell in C that mimics the core behavior of Bash. This project requires a deep understanding of process creation (forking), file descriptor manipulation, input parsing, and signal handling.

## Features

* Displays a prompt when waiting for a new command.
* Executes system commands using the `PATH` environment variable or via absolute/relative paths.
* Handles output and input redirections: `<`, `>`, `<<` (heredoc), and `>>` (append).
* Implements pipes (`|`), connecting the output of one command to the input of the next.
* Expands environment variables (e.g., `$USER` or `$?`).
* Properly handles signals (`Ctrl-C`, `Ctrl-D`, and `Ctrl-\`).
* Includes basic built-in commands: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## Bonus Features

The bonus part introduces more complex parsing and expansion mechanics. Based on the implementation:

* **Logical Operators and Parentheses:** Utilizes an Abstract Syntax Tree (AST) to properly parse and execute `&&`, `||`, and subshells `()` with correct precedence.
* **Wildcards (Globbing):** Implements support for the `*` wildcard, expanding arguments to match filenames in the current working directory.

## Dependencies

To compile and execute this project, the following packages must be installed on your system:

* A C compiler (`gcc` or `clang`)
* `make`
* GNU `readline` library

## Instructions

1. **Clone the repository:**
```bash
git clone <your_repository_url>
cd minishell

```

2. **Compilation:**
To compile the standard version of the shell, run:
```bash
make

```

To compile the shell with the bonus features included, run:
```bash
make bonus

```

3. **Execution:**
Launch the shell by running:
```bash
./minishell

```

Or, if you compiled the bonus version:
```bash
./minishell_bonus

```

4. **Cleaning up:**
* `make clean`: Deletes all compiled object files.
* `make fclean`: Deletes object files and the generated executables.
* `make re`: Fully cleans and recompiles the project.

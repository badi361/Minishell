# 42 Minishell Project

Minishell
As the name implies, this project is about creating a simple shell in C, taking bash as a reference. Impementation of clasic bash written completely from scratch with Yusuf Anıl Turgut as part of 42 Ciriculum.

  * This custom shell has most of the features from original bash like custom enironment, builtins, pipes, multiple redirections, logical operators and parenthesis, signal and error      handling.
  * It works by geting input from user. Then dividing it into tokens. Then parsing it into varios data structures and executing.

GETTING STARTED

Prerequisites
  * GCC compiler
  * Make utility
  * GNU readline
Building

# Clone the repository:
$ git clone https://github.com/badi361/Minishell

# Change directory to the project directory and compile;
$ cd minishell && make

# To run the shell, simply execute the following command:
$ ./minishell

Features
Command execution
  * The shell supports executing external commands, built-in commands, and pipeline commands.
### Input/output redirection
  * The shell supports input/output redirection using the < and > characters.
Signal handling
  * The shell handles the following signals:

  * SIGINT (Interrupt signal)
  * SIGQUIT (Quit signal)
Environment variables
  * The shell supports creating, modifying, and deleting environment variables using the export and unset built-in commands.
Command history
  * The shell supports command history using the readline library.
Built-in commands
  * The shell supports the following built-in commands:

  * echo - displays a message
  * cd - changes the current directory
  * pwd - prints the current working directory
  * export - creates or modifies an environment variable
  * unset - deletes an environment variable
  * env - prints the environment variables

Acknowledgments

  * This project was inspired by the Unix shell, and was built using the following resources:

  * The readline library documentation
  * The Bash shell documentation

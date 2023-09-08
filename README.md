# minishell

**Recreate BASH**
The development of bash (or the Bourne-again shell) dates back to as early as 1988 as an extension to the existing unix shells which were used by developers.
But not just because of its historical importancy, but also because to date many developers use bash or its successors, it is a insightful and challenging exercise to try to recreate Bash in the language that it has been decelopend: **C**.

The goal of this project was simple: Recreate Bash!
But in order to do so, one had to learn 

## Learning goals
- Comprehend and master the challenges in writing a lexer, parser, expander and executor to recreate bashs functionality
- Learn to collaborate on a coding project which means to split, review and integrate code

## Core features
Features of this implementation are (selected)
- execute binaries given an absolute, relative path or using the PATH environment variable
- implement the 
- redirections (>, <, >>) and heredoc
- concatenations of commands using pipe operators, semicolon, and (&&), or (||)
- implement regular expressions to handle the asterisk
- read, save and manipulate environment variables

## Usage

### Installation
1. clone the repository
2. change the directory to the cloned folder 
3. type ```make```

### Execution
launch the shell with 

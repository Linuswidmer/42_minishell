# minishell

**Recreate BASH!**
The development of bash (or the Bourne-again shell) dates back to as early as 1988. 
It was introduced as an extension to the existing unix shells introducing many new features that enhanced software development. \
Till this day, bash is updated and it is stil the preffered command line interface for millions of developers. And it is what scares most non-software affiliated people away from digging into the depths of computers.
But not just because of its historical importancy, but also because to date many developers use bash or its successors, 
it is a insightful and challenging exercise to try to recreate Bash in the language that it has been decelopend: **C**.

## Learning goals
- Getting comforatble with more advanced features of bash, like manipulating using environment variables, redirecting output, chaining of commands etc.
- Understand thoroughly Lexer, Parser, Expander and Executor, which are core concepts not only of shells but can be found in many applications.
- Learn to collaborate on a coding project which means to split, review and integrate code.

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
launch the shell with ```./minishell```

## Resources

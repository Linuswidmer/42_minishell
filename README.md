# minishell

#### **Recreate BASH!**
The development of bash (Bourne-again shell) dates back to as early as 1988. 
It was introduced as an extension to the existing unix shells introducing many new features that enhanced software development. \
Till this day, bash is updated and stil the preffered command line interface for developers across the globe. And probably it is also what makes most most non-software affiliated people jump back, as soon as they see *TERMINAL*...
So what would be better to take a deep dive into the logic of shells and writing our first bigger program than recreating bash in the language it is being developed... **C**

## Learning goals
- Understand the concept and division of labor of between the Lexer, Parser, Expander & Executor which lie at the core of many applications that involve complex user input processing.
- Concurrently getting comforatble with core features of bash, e.g. environment variables, (multi-) redirection of output, chaining of commands etc.
- Learn to collaborate on a coding project which means developing strategies to split, review and integrate code.
- Learning how to do *Reverse Engineering*
- Maintaining a bigger code base. So far we had only worked on small scale projects but when this project unravelled into more that 5000 lines if code, one had to come up with a system for files, naming conventions, documentation...

## Core features
Some selected features of this implementation are
- execute binaries given an absolute, relative path or using the PATH environment variable
- standard i/o redirections (>, <, >>), as well as the heredoc
- implement recursion for subshells "()" with their i/o redirection
- executing multiple commands simulaneously and subsequently with pipe operators, semicolon ,
- logical concatenation of commands using and (&&), or (||)
- implement regular expressions to handle the asterisk "*"
- read, save and manipulate environment variables
- handle signals CTRL+D, CTRL+C, CTRL+/
- ...

## Usage

### Installation
1. clone the repository ```git clone <ssh/http> <name of folder>```
2. change directory to the cloned folder ```cd <name of folder>``` 
3. run ```make```

### Execution
1. launch the shell with ```./minishell```
2. go crazy! really, we encourage you to try the most absurd inputs, for inspiration \
   ```export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8 ; echo "$A'$B"'$C"$D'$E'"$F'"'$G'$H"``` (testing single and double quotes) \
   ``` (ls && pwd | wc) >> hola ; echo hey&&(ls && pwd | wc) > hola ; cat hola``` (redirections, operators) \
   ```cat | cat | ls ``` (our favourite one 😉) \
3. Exit the shell with CTRL+D or execute ```exit``` 

## Resources
- ```bash```
- RTFM

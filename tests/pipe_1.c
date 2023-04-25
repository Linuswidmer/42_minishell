#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>





int ft_pipe(char *path, char **arg, char **envp, char last, int outfd)
{
	int	pipefd[2];
	int	pid; 
	
	if (last)
	{
		if (dup2(outfd, STDOUT_FILENO) == -1) 
            return (1);
	/*	if (close(outfd) == -1)
            return (1);*/
	}
	else
	{
		if (pipe(pipefd) == -1)
			return (1);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (1);
		if (close(pipefd[1]) == -1)
			return (1);
	}
	pid = fork ();
	if (pid == -1)
		return (1);
	if (!pid)
	{
	/* min_next_node(*/
		if(execve(path, arg, envp) == -1)		
		{
			close(pipefd[0]);
			return (1);		
		}
	}
	if (!last)
	{	if (dup2(pipefd[0], STDIN_FILENO) == -1)
        	return (1);
		if (close(pipefd[0]) == -1)
        	return (1);
	}
	return (0);	
}
/*
int ft_pipe_node() 
{
  int error;
    int n;

	int out_fd = dup(STDOUT_FILENO);
    char *cmd1 = "/usr/bin/yes";
    char *arg1[] = {"", NULL};
    char *cmd2 = "/usr/bin/head";
    char *arg2[] = {"head",  NULL};
    char *cmd3 = "/usr/bin/cat";
    char *arg3[] = {"cat", NULL};
    error = 0;
    n = 0;


    while (n++ < 3 && !error)
    {
        if (n == 1)
            error = ft_pipe(cmd1, arg1, envp, 0, out_fd);
        if (n == 2)
             error = ft_pipe(cmd2, arg2, envp, 0, out_fd);
        if (n == 3)
             error = ft_pipe(cmd3, arg3, envp, 1, out_fd);
    }
    if (!error)
        {
            while ( n--)
                waitpid(-1, NULL, 0);
            printf("parent  finsihed\n");
            close(out_fd);    
        }
    else
    {                                 
        dup2(out_fd, STDOUT_FILENO) 
        printf("child  finsihed\n");
        close(out_fd);
    }
	return (error);
}

*/




int main (int argc, char **argv, char** envp)
{
  int error;
    int n;
	(void)argc;
	(void)argv;
	
    int out_fd = dup(STDOUT_FILENO);
    char *cmd1 = "/usr/bin/yes";
    char *arg1[] = {"", NULL};
    char *cmd2 = "/usr/bin/head";
    char *arg2[] = {"head",  NULL};
    char *cmd3 = "/usr/bin/cat";
    char *arg3[] = {"cat", NULL};
    error = 0;
    n = 0;


    while (n++ < 3 && !error)
    {
        if (n == 1)
            error = ft_pipe(cmd1, arg1, envp, 0, out_fd);
        if (n == 2)
             error = ft_pipe(cmd2, arg2, envp, 0, out_fd);
        if (n == 3)
             error = ft_pipe(cmd3, arg3, envp, 1, out_fd);
    }
    if (!error)
        {
            while ( n--)
                waitpid(-1, NULL, 0);
            printf("parent  finsihed\n");
            close(out_fd);
        }
    else
    {
        dup2(out_fd, STDOUT_FILENO);
        printf("child  finsihed\n");
        close(out_fd);
    }
    return (error);
}

 





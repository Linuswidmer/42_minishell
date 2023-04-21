#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int global_exit = 0;

int ft_pipe(char *path, char **arg, char **envp, char last, int outfd)
{
	int	pipefd[2];
	int a = 0; 
	int pid;
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
	if (!pid)
	{
		if (!last)
		{
			{
				while (a < 100000)
					a++;
			}
			return (12);
		}
		return (1);
	/*
		if(execve(path, arg, envp) == -1)		
		{
			close(pipefd[0]);
			return (1);		
		}
	*/
	}
	if (!last)
	{	if (dup2(pipefd[0], STDIN_FILENO) == -1)
        	return (1);
		if (close(pipefd[0]) == -1)
        	return (1);
	}
	return (0);	
}

int *child_processes()
{
	int *pid;
	int n;

	pid = malloc(sizeof(int) *3);
	n = 0;
    while (n++ < 3 && !global_exit)
    {
		pid[n - 1] = fork ();
		if (!pid[n -1])
		{
			
			if (n != 3)
        	{
            	{
					int a = 0;
                	while (a < 100000)
                    	a++;
            	}
             	global_exit = 12;
        	}	
        	else 
				global_exit = 1;
		}

	}
	return (pid);
}

int main (int argc, char **argv, char** envp)
{
  int error;
    int n;
	int status;
	int *pid;

    int out_fd = dup(STDOUT_FILENO);
    char *cmd1 = "/usr/bin/l";
    char *arg1[] = {"", NULL};
    char *cmd2 = "/usr/bin/grep";
    char *arg2[] = {"grep", "cl", NULL};
    char *cmd3 = "/usr/bin/cat";
    char *arg3[] = {"cat", NULL};
    error = 0;
    n = 0;


	pid = child_processes();
		   
    if (!global_exit)
        {
			n = 0;
            while ( n < 3)
			{
                waitpid(pid[n]  , &status, 0);
				printf("pid is %i\n", pid[n]);
				if ( pid[n] == pid[2])
					printf("%i\n", WEXITSTATUS(status));
				n++;
            }
			printf("parent  finsihed\n");
            close(out_fd);
            return (error);
        }
    else
    {
        dup2(out_fd, STDOUT_FILENO);
        printf("child  finsihed\n");
        close(out_fd);
        return (global_exit);
    }
}


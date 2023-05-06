# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

void exec_child(int in_fd, int out_fd, char **args, char *path)
{
	printf("in fd: %i\n", in_fd);
	printf("out fd: %i\n", out_fd);
	printf("\n");

	dup2(out_fd, STDOUT_FILENO);
	close (out_fd);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	execve(path, args, NULL);
	perror("execve");
	exit(0);
}

int main()
{
	int pipefd[2];
	int *old_pipefd;
	pid_t *pid;
	char* cat_cmd[] = {"cat", NULL};
	char* ls_cmd[] = {"ls", NULL};
	int i;
	int fdout;
	int fdin;

	fdout = dup(STDOUT_FILENO);
	fdin = dup(STDIN_FILENO);

	i = 0;
	pid = malloc(sizeof(pid_t) * 3);
	old_pipefd = malloc(sizeof(int) * 2);
	while (i < 3)
	{
		pipe(pipefd);
		pid[i] = fork();
		if (pid[i])
		{	
			if ( i > 0)
			{
				close(old_pipefd[0]);
				close(old_pipefd[1]);
			}

		}	
		if (!pid[i])
		{
			if (i == 0)
			{
				close (pipefd[0]);
				close (fdout);
				exec_child(fdin, pipefd[1], cat_cmd, "/bin/cat");
			}
			if (i == 2)
			{
				close (old_pipefd[1]);
				close (pipefd[0]);
				close (pipefd[1]);
				close(fdin);
				exec_child(old_pipefd[0], fdout, ls_cmd, "/bin/ls");
			}
			else
			{
				close (old_pipefd[1]);
				close (pipefd[0]);
				close (fdout);
				close(fdin);
				exec_child(old_pipefd[0], pipefd[1], cat_cmd, "/bin/cat");
			}
		}
		old_pipefd[0] = pipefd[0];
		old_pipefd[1] = pipefd[1];
		//close (pipefd[0]);
		//close (pipefd[1]);
		i++;
	}
	close(old_pipefd[0]);
	close(old_pipefd[1]);
	close (pipefd[0]);
    close (pipefd[1]);
	close(fdout);
}

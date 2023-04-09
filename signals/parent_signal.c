/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:35:06 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 19:18:33 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


#define READ_END 0
#define WRITE_END 1

void handle_sigpipe(int sig) 
{
	printf("Received SIGPIPE signal\n");
}

int main()
{
    int fd[2];
    pid_t pid1, pid2;
    int status;

	struct sigaction sa_sigpipe;

	sa_sigpipe.sa_handler = handle_sigpipe;
	sigemptyset(&sa_sigpipe.sa_mask);
	sa_sigpipe.sa_flags = 0;

	if (sigaction(SIGPIPE, &sa_sigpipe, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process to execute the "yes" command
    
	pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        // Child process 1: execute "yes" command
        close(fd[READ_END]); // close unused read end of the pipe
        dup2(fd[WRITE_END], STDOUT_FILENO); // redirect stdout to the pipe
        close(fd[WRITE_END]); // close write end of the pipe

        // execute "yes" command
        char *args[] = {"yes", NULL};
        execve("/bin/yes", args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Fork a second child process to execute the "head" command
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        // Child process 2: execute "head" command
        close(fd[WRITE_END]); // close unused write end of the pipe
        dup2(fd[READ_END], STDIN_FILENO); // redirect stdin to the pipe
        close(fd[READ_END]); // close read end of the pipe

        char *args[] = {"head", NULL};
        execve("/bin/head", args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    close(fd[0]); // Close unused write end of the pipe
    close(fd[1]); // Close unused write end of the pipe
    // Wait for both child processes to exit
	pid_t wpid1 = waitpid(pid1, &status, 0);
    //printf("%i\n", wpid1);
	printf("Child exit status is %d\n", WEXITSTATUS(status));
    printf("Child process terminated with signal %d\n", WTERMSIG(status));
	pid_t wpid2 = waitpid(pid2, &status, 0);
	//waitpid(-1, NULL, 0);
	//pid2 = fork()	
    printf("Child exit status is %d\n", WEXITSTATUS(status));
    printf("Child process terminated with signal %d\n", WTERMSIG(status));
    return 0;
}


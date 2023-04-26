/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:10:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 10:57:52 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

void handle_sigint(int sig)
{
	printf("\n");
}

void handle_sigint_heredoc(int sig);
{
	exit(1);
}

int init_signals(void)
{
    struct sigaction sa_sigint;

    sa_sigint.sa_handler = handle_sigint;
    sigemptyset(&sa_sigint.sa_mask);
    sa_sigint.sa_flags = 0;

    if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
    {
        perror("sigaction");
        return (1);
    }
	return (0);
}


int main()
{
	int pid;
	int fd;
	char input[101];
	int n;

	fd = open("tmpfile", O_CREAT | O_WRONLY | O_TRUNC);	
	init_signals();
	while (1)
	{
		n = read(0, input, 100);
		input[n] = '\0';
		//printf("%s", input);
		if (strncmp(input, "END", 3) == 0)
			break;
		write(fd, input, n);
	}
}

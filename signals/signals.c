/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:33:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 14:33:03 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_sigint(int sig) 
{
	printf("\n");
}

void handle_sigquit(int sig) {
    printf("Received SIGQUIT signal\n");
	exit(1);
}

void handle_sighup(int sig) {
	printf("Received SIGHUP signal\n");
	exit (0);
}

int main() 
{
	//signal(SIGINT, handle_sigint);
	
	struct sigaction sa_sigint;
	struct sigaction sa_sigquit;

	sa_sigint.sa_handler = handle_sigint;
	sigemptyset(&sa_sigint.sa_mask);
	sa_sigint.sa_flags = 0;

	sa_sigquit.sa_handler = handle_sigquit;
    sigemptyset(&sa_sigquit.sa_mask);
    sa_sigquit.sa_flags = 0;

	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	if (sigaction(SIGQUIT, &sa_sigquit, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
	while (1)
	{

	}

	return 0;
}

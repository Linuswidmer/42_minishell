/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:33:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 12:49:18 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_sigint(int sig) 
{
	printf("\n");
	exit (0);
}

void handle_sighup(int sig) {
	printf("Received SIGHUP signal\n");
	exit (0);
}

int main() 
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sighup);
	while (1)
	{

	}

	return 0;
}

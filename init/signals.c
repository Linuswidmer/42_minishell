/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:52:07 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/09 12:15:56 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig) 
{
	printf("\n");
	//kill(0, SIGTERM);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
}

void sigint_in_job(int sig)
{
	kill(0, SIGINT);
	ft_printf_fd("kill\n",2);
}

int init_signals(void)
{
	struct sigaction sa_sigint;
	struct sigaction sa_sigquit;

	sa_sigint.sa_handler = handle_sigint;
	sigemptyset(&sa_sigint.sa_mask);
	sa_sigint.sa_flags = 0;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
  return (0);
}

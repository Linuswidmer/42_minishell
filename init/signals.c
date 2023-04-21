/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:52:07 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 10:52:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void handle_sigint(int sig) 
{
  printf("\n");
  rl_on_new_line();
  rl_replace_line("", 0); // second parameter not yet understood
  rl_redisplay();
}

void handle_sigquit(int sig) 
{
  // not sure how i stop CTRL + \  from making their weird thing
}

int init_signals(void)
{
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
    return (1);
  }
  return (0);
}

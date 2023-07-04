/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:52:07 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/04 11:38:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_status != 155)
		{
			rl_redisplay();
		}
		if (g_status == 155)
			g_status = 130;
	}
}

void	handle_signals_cmd(int sig)
{
	if (sig == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDERR_FILENO, "Quit(core dumped)\n", 18);
}

int	init_signals_cmd(void)
{
	struct sigaction	sa_signals;

	sa_signals.sa_handler = handle_signals_cmd;
	sigemptyset(&sa_signals.sa_mask);
	sa_signals.sa_flags = 0;
	signal(SIGINT, handle_signals_cmd);
	signal(SIGQUIT, handle_signals_cmd);
	signal(SIGQUIT, SIG_DFL);
	if (sigaction(SIGINT, &sa_signals, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	if (sigaction(SIGQUIT, &sa_signals, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	return (0);
}

int	init_signals(void)
{
	struct sigaction	sa_signals;

	sa_signals.sa_handler = handle_signals;
	sigemptyset(&sa_signals.sa_mask);
	sa_signals.sa_flags = 0;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa_signals, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	return (0);
}

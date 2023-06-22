/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipestruct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:09:30 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/22 14:10:04 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipestruct(t_pipestruct *pipes)
{
	free(pipes->pipefd);
	free(pipes->old_pipefd);
	free(pipes->pid);
	free(pipes);
}

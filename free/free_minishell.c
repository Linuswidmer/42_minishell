/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:34:48 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/27 12:34:58 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_min *min)
{
	close(min->in);
	close(min->out);
	free_dict(min->dict);
	free_builtins(min->builtins);
	free_min(min);
}


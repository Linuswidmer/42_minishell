/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:41:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/29 14:54:40 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void	ft_print_cmd(t_cmdnode       *cmdnode)
{
	ft_printf_fd("CMDNODE\n", 2);
	while (cmdnode)
	{
		ft_printf_fd("CMD: *%s*\n", 2, cmdnode->arg);
		cmdnode = cmdnode->next;
	}
	 ft_printf_fd("\n", 2);
}

int	min_expander(t_lexer *token, t_dict *dict, t_lexer *end, char ***cmd)
{
	t_cmdnode	*cmdnode;
	int			exit;

	exit = 0;
	cmdnode = NULL;
	while (token != end && !exit)
	{	
		if (min_token_is_io(token->key))
			exit = min_set_io(&token, dict);
		else if (token->key == l_space)
			token = token->next;
		else
			exit = min_set_cmd(&token, dict, &cmdnode);
	}
	if (!exit && cmd)
	{
		if (_DEBUG1)
			ft_print_cmd(cmdnode);
		*cmd = min_ex_get_cmd(cmdnode);
		if (!**cmd)
			exit = 1;
	}
	//min_free_cmdnode(&cmdnode);		
	return (exit);
}

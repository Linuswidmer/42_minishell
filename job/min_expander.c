/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:41:03 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/05 17:26:36 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_expander(t_lexer *token, t_dict *dict, t_lexer *end, char ***cmd)
{
	t_cmdnode *cmdnode;
	int exit;
	
	exit = 0;
	cmdnode = NULL;	
	while (token != end && !exit)
	{	
		if (min_token_is_io(token->key))
		{			
            		exit = min_set_io(&token, dict);
            	}	
 		else if (token->key == l_space)
 		{
	
			token = token->next;
		}	
		else
		{
			exit = min_set_cmd(&token, dict, &cmdnode);
		}	
	}
	if (!exit && cmd)
	{
		*cmd = min_ex_get_cmd(cmdnode);
		if (!**cmd)
			exit = 1;	
	}
	//min_free_cmdnode(&cmdnode);		
	return (exit);
}

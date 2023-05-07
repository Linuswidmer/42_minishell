/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:48:22 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 09:48:37 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_token_list(t_lexer **token_list)
{
  t_lexer *tmp;

  while (*token_list)
  {
    tmp = (*token_list)->next;
    if (*token_list)
    {
    	if ((*token_list)->value)
		free((*token_list)->value);
	free(*token_list);
    }
    *token_list = tmp;
  }
  //free(token_list);
 
}


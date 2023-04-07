/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src_lexer/expander.c
/*   Created: 2023/04/07 09:43:16 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 09:43:27 by lwidmer          ###   ########.fr       */
=======
/*   Created: 2023/04/01 16:55:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 16:17:14 by jstrotbe         ###   ########.fr       */
>>>>>>> dev_jstrotbe:lexer_module/lexer.h
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void expand_dollar_tokens(t_lexer *first)
{
<<<<<<< HEAD:src_lexer/expander.c
	char *varname;
=======
	l_empty,
	l_dquote,
	l_quote,
	l_word,
	l_asterisk,
	l_paropen,
	l_parclose,
	l_heredoc,
	l_append,
	l_in,
	l_out,
	l_and,
	l_or,
	l_semi,
	l_pipe,
	l_escape,
} t_lexertype ;	
>>>>>>> dev_jstrotbe:lexer_module/lexer.h

	while (first)
	{
		if (first->key == l_dollar)
		{
			first->key = l_word;
			varname = first->value;
			first->value = ft_strdup("content");
			free(varname);
		}
		first = first->next;
	}
}

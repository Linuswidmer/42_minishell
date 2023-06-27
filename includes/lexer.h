/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:55:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/27 12:09:19 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/04/09 22:09:45 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_lexertype	check_token(char *input, int pos);

t_lexer		*lexer(char **input);

int			parse_dollar(char *input, int pos, t_lexer *tmp);
int			parse_quote(char *input, int pos, t_lexer *tmp, t_lexertype token);

/* token_parser.c */
int			parse_token_to_list(t_lexertype current_token, char *input,
				int pos, t_lexer *tmp);

void		expand_dollar_tokens(t_lexer *first);

/* token _list_utils.c */
t_lexer		*add_to_token_list(t_lexer *list_end, char *str,
				int start, int pos);
t_lexer		*remove_token_from_list_end(t_lexer *list_end);
int			key_value_to_token(t_lexer *token, t_lexertype key, char *input,
				int len);

/*dollar_postprocesing */
t_lexer		*dollar_postprocessing(t_lexer *tmp);

/* lexer_utils.c */
int			skip_space_tab(char *input, int pos);
t_lexer		*init_lexer_struct(void);
#endif

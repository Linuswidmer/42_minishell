/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:27:39 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/24 12:40:14 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANDER_H
# define EXPANDER_H

/* functions */

char 	**min_asterisk(t_expander *word);
void	min_dollar(t_lexer **token, t_expander **word, t_dict *dict);
void	min_free_expander(t_expander **node);
t_expander *min_init_expander(t_lexertype key);
t_expander *min_last_expander(t_expander *node);
void	min_word(t_lexer **token, t_expander **word);
char **min_word_eval(t_lexer **token, t_dict *dict);

#endif

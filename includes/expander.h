/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:27:39 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/11 11:05:22 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANDER_H
# define EXPANDER_H

/* functions */

//char 	**min_asterisk(t_expander *word);
//void	min_dollar(t_lexer **token, t_expander **word, t_dict *dict);
void	min_free_expander(t_expander **node);
t_expander *min_init_expander(t_lexertype key, char *value);
t_expander *min_last_expander(t_expander *node);
char    min_word(t_lexer **token, t_expander **word, char *value,  char space);
char **min_word_eval(t_lexer **token, t_dict *dict);
t_exphelp    min_init_exphelp(t_dict *dict, char word, char space );
char    min_til(t_lexer **token, t_expander **word, t_dict *dict, char space);
char            min_dollar(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help);
char    min_asterisk(t_lexer **token, t_expander **word, t_expander *old, t_exphelp help);
void    min_evaluate_asterisk(t_expander **word, t_expander *asterisk, char wo);
void    min_add_extra_to_word(t_expander **word, t_expander *extra);
int     min_addlast_expander(t_expander **word, char *value, char *wo);

/*debug*/
void  min_print_asterisk(t_expander *asterisk);
#endif

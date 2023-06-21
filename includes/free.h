/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:11:55 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/08 15:00:40 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H



void    min_free(char **tofree);
void	min_dfree(char ***tofree);
/**/
void double_free(char ***str);

/* free_lexer */
void ft_free_token_list(t_lexer **list);
void free_token_list(t_lexer **token_list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:11:55 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 12:39:19 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

void	min_free(char **tofree);
void	min_dfree(char ***tofree);
/**/
void	double_free(char ***str);

void	free_token_list(t_lexer **token_list);
void	free_pipestruct(t_pipestruct *pipes);
void	free_minishell(t_min *min);
#endif

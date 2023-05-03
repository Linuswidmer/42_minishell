/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:08:17 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/03 09:47:43 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

int     min_job(t_ast *ast, t_dict *dict, t_builtins *build, char fork);
int	min_executer(t_ast *ast, t_dict *dict, t_builtins *build, char fork);
int 	min_exit_handler(int exit);
int min_sub(t_ast *ast, t_dict *dict, t_builtins *build);
int min_route(t_ast *ast, t_dict *dict, t_builtins *build);

#endif

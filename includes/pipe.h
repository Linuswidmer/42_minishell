/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:07:22 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/28 14:16:49 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

int	pipe_redirect_first(t_pipestruct *pipes);
int	pipe_redirect_middle(t_pipestruct *pipes);
int	pipe_redirect_last(t_pipestruct *pipes);
int min_pipe(t_pipenode *pipe, t_dict *dict, t_builtins *build);
int	min_pipe_loop(t_pipenode *pipenode, t_dict *dict, t_builtins *builtin, t_pipestruct *pipes);
#endif


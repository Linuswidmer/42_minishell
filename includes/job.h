/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:45:11 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 12:44:19 by lwidmer          ###   ########.fr       */
/*   Updated: 2023/05/03 09:32:23 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

void		min_free_cmdnode(t_cmdnode **cmdnode, int exit);

char		**min_ex_get_cmd(t_cmdnode *cmd);

int			min_ex_io(t_lexertype key, char *filename, char *heredoc);

int			min_set_cmd(t_lexer **token, t_dict *dict, t_cmdnode **cmd);

int			min_set_io(t_lexer **token, t_dict *dict);

int			min_expander(t_lexer *token, t_dict *dict, t_lexer *end,
				char ***cmd);

int			min_io_and_cmd(t_jobnode *astjob, t_dict *dict, char ***cmd);

/* common */
int			min_common_cmd(t_jobnode *astjob, t_dict *dict, char f);

int			ft_checkpath(char *cmd, t_dict *dict, char **path);

char *const	*min_get_envp(t_dict *dict);

/* buildin */
int			min_buildin_cmd(t_jobnode *astjob, t_dict *dict, t_builtins *build);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:41:35 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/06 12:50:11 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* export.c */
void		print_dict_export(t_dict *dict);
int			min_export(t_dict *dict, char **arg);

/* cd.c */
int			min_cd(t_dict *dict, char **arg);

/* pwd */
int			min_pwd(char **args);

/* env.c */
int			min_env(t_dict *dict, char **args);

/* echo.c */
int			min_echo(char **arg);

/* exit.c */
int			min_exit(char **arg);

/* unset.c */
int			min_unset(t_dict **dict, char **arg);

/* buitins.c */
void		create_builtin_commands(t_min *min);
t_builtins	*create_builtins(t_dict *dict, t_commands *commands);

/* builtins_wrapper.c */
int			export_wrapper(t_builtins *builtin, char **args);
int			cd_wrapper(t_builtins *builtin, char **args);
int			pwd_wrapper(t_builtins *builtin, char **args);
int			env_wrapper(t_builtins *builtin, char **args);
int			exit_wrapper(t_builtins *builtin, char **args);
int			echo_wrapper(t_builtins *builtin, char **args);
int			unset_wrapper(t_builtins *builtin, char **args);

#endif

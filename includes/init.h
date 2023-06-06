/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:50:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/06/06 12:52:31 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

/* signals.c */
int		init_signals(void);
int		init_signals_cmd(void);

/* dict.c */
t_dict	*init_env_variable(void);
int		create_dict_on_startup(char **env, t_dict **p_dict);

/* min_dict_utils.c */
int		write_to_dict(t_dict *var, char *key, char *value);
t_dict	*search_key_in_dict(t_dict *var, char *arg);
t_dict	*get_dict_last(t_dict *dict);
int		write_new_entry_to_dict(t_dict *dict, char *new_key, char *new_value);

/*init.c*/
int		init_minishell(t_min **min, char **env);

/* free_dict_builtins_min */
int		free_dict(t_dict *dict);
int		free_builtins(t_builtins *builtins);
int		free_min(t_min *min);

/* export_utils */
int		export_no_dictionary(void);
int		export_not_valid_identifier(char *arg);
int		export_check_if_only_digits(char *arg);
int		export_check_if_key_is_valid(char *arg);

/* min_shlvl */
int		min_update_shlvl_on_startup(t_dict *dict);
#endif

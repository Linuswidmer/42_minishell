/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/10 10:53:45 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_directories_in_dict(char *pwd, t_dict *dict)
{
	t_dict	*tmp;
	t_dict	*dict_pwd;
	t_dict	*dict_oldpwd;

	dict_pwd = search_key_in_dict(dict, "PWD");
	dict_oldpwd = search_key_in_dict(dict, "OLDPWD");
	if (dict_oldpwd && dict_pwd)
	{
		free(dict_oldpwd->value);
		dict_oldpwd->value = dict_pwd->value;
		dict_pwd->value = ft_strdup(pwd);
	}
	else if (dict_pwd)
	{
		dict_pwd->value = ft_strdup(pwd);
		dict_oldpwd->value = ft_strdup("");
	}
	return (0);
}

static int	cd_to_oldpwd(t_dict *dict)
{
	int		status;
	t_dict	*dict_oldpwd;

	dict_oldpwd = search_key_in_dict(dict, "OLDPWD");
	if (dict_oldpwd)
		status = chdir(dict_oldpwd->value);
	else
	{
		ft_printf_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (status == -1)
	{
		ft_printf_fd("cd: %s: No such file or directory\n", 2,
			dict_oldpwd->value);
		return (1);
	}
	else
		return (0);
}

static int	cd_to_home(t_dict *dict)
{
	int		status;
	t_dict	*dict_home;

	dict_home = search_key_in_dict(dict, "HOME");
	if (dict_home)
	{
		status = chdir(dict_home->value);
		if (status == -1)
		{
			ft_printf_fd("cd: %s: No such file or directory\n", 2,
				dict_home->value);
			return (1);
		}
		else
			return (0);
	}
	else
	{
		ft_printf_fd("cd: HOME not set\n", 2);
		return (1);
	}
}

static int	cd_to_arg(char *arg)
{
	int	status;

	status = chdir(arg);
	if (status == -1)
	{
		ft_printf_fd("%s: No such file or directory\n", 2, arg);
		return (1);
	}
	return (0);
}

int	min_cd(t_dict *dict, char **arg)
{
	int		status;
	char	*pwd;

	if (arg[1])
	{
		ft_printf_fd("cd: too many arguments", 2);
		return (1002);
	}	
	if (!arg[0])
		status = cd_to_home(dict);
	else if (ft_strncmp(arg[0], "-", ft_strlen(arg[0])) == 0)
		status = cd_to_oldpwd(dict);
	else
		status = cd_to_arg(arg[0]);
	pwd = getcwd(NULL, 0);
	if (!status)
		printf("%s\n", pwd);
	update_directories_in_dict(pwd, dict);
	free(pwd);
	return (1000 + status);
}

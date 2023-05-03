/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/28 19:57:57 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int update_directories_in_dict(char *pwd, t_dict *dict_pwd, t_dict *dict_oldpwd)
{
  if (dict_oldpwd && dict_pwd)
  {
	printf("pwd %s\n", dict_pwd->value);
	printf("oldpwd %s\n", dict_oldpwd->value);
    //free(dict_oldpwd->value);
    dict_oldpwd->value = dict_pwd->value;
  }
  else if (dict_pwd)
    write_to_dict(dict_pwd, "PWD", pwd);

  return (0);
}

static int cd_to_oldpwd(t_dict *dict_oldpwd)
{
  int status;

  if (dict_oldpwd)
  {
    status = chdir(dict_oldpwd->value);  
  }
  else
  {
    printf("cd: OLDPWD not set\n");
    return (1);
  }
	if (status == -1)
  {
    printf("cd: %s: No such file or directory\n", dict_oldpwd->value);
		return (1);
  }
  else
    return (0);
}

static int cd_to_home(t_dict *dict_home)
{
  int status;

  if (dict_home)
    status = chdir(dict_home->value);  
  else
  {
    printf("cd: HOME not set\n");
    return (1);
  }
	if (status == -1)
  {
    printf("cd: %s: No such file or directory\n", dict_home->value);
		return (1);
  }
  else
    return (0);
}

int min_cd(t_dict *dict, char **arg)
{
    int status;
    char *pwd;
	t_dict *dict_home;
	t_dict *dict_pwd;
	t_dict *dict_oldpwd;
	
	if (arg[2])
	{
		printf("cd: too many arguments");
		return (1002);
	}	

	dict_pwd = search_key_in_dict(dict, "PWD");
	dict_oldpwd = search_key_in_dict(dict, "OLDPWD");
	dict_home = search_key_in_dict(dict, "HOME");

	if (ft_strncmp(arg[1], "-", ft_strlen(arg[1])) == 0)
		status = cd_to_oldpwd(dict_oldpwd);
	else if (arg[1] == NULL || ft_strncmp(arg[1], "~", ft_strlen(arg[1])) == 0)
		status = cd_to_home(dict_home);
	else
	{
		status = chdir(arg[1]);
		if (status == -1)
		{
			printf("%s: No such file or directory\n", arg[1]);
			return (1002);
		}
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	update_directories_in_dict(pwd, dict_pwd, dict_oldpwd);
	free(pwd);
	return (1000);
}

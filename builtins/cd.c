/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 17:04:19 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int cd(char *arg, t_dict *dict)
{

    int status;
    char *pwd;
	t_dict *dict_pwd;
	t_dict *dict_oldpwd;

    status = chdir(arg);
	// wenn die nicht gefunden werden, werde auch keine neue variablen kreiert..
	dict_oldpwd()
	if (status = -1)
		return (-1);
    pwd = getcwd(NULL, 0);
    dict_pwd = search_in_dict(dict, "PWD");
	write_to_env_variable(dict_pwd, "PWD", pwd);
	printf("%s\n", pwd);
    free(pwd);
    pwd = NULL;
    return (0);
}

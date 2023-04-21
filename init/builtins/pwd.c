/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:44:38 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 17:08:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int min_pwd(char **args)
{
	char *pwd;
 
	if(args[0])
		printf("pwd: too many arguments\n");
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
    	return (1);
}

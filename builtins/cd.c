/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:25 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 12:05:23 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int cd(char *arg)
{

    int i;

    i = chdir(arg);
    printf("%i\n", i);
    char *pwd;
    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);
    pwd = NULL;
    return (0);
}

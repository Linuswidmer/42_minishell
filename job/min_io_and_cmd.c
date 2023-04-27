/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_io_and_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:33:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/27 12:51:30 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int ft_io_and_cmd(t_jobnode *astjob, t_dict *dict, char ***cmd)
{

    return (min_expander(astjob->start, dict, astjob->last, cmd));
}


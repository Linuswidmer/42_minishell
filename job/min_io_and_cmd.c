/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_io_and_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:33:01 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/05 17:19:26 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int min_io_and_cmd(t_jobnode *astjob, t_dict *dict, char ***cmd)
{

    return (min_expander(astjob->start, dict, astjob->last, cmd));
}


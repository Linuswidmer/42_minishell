/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_exit_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:27:38 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 11:56:22 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	min_exit_handler(int exit)
{
	if (exit == 1000 || exit == 2000)
		return (256);
	if (exit >= 3000)
		return (exit);
	if (exit > 1000 && exit < 2000)
		return (exit - 1000);
	if (exit > 2000)
		return (exit - 2000);
	else 
		return (exit);
}

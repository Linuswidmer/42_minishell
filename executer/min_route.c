/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_route.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:30:25 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/05/02 14:55:28 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_count_routenode(t_routenode *route)
{
	int c;

	c = 0;
	while (route)
	{
		c++;
		if (route->next)
			route = route->next->node.route;
		else
			route = NULL;
	}
	return (c);
}




int	min_route(t_ast *ast, t_dict *dict, t_builtins *build)
{

	int exit;
	int len;
	t_ast *new;
	
	new = ast;
	exit = 0;
	len = ft_count_routenode(new->node.route);
	printf("len: %i\n", len);

	exit = min_executer(new->node.route->down, dict, build);
	
	while (exit >= 1000 && exit < 2000)
	{
		printf("exit: %i\n", exit);
			g_status = exit - 1000;
			if (ast->node.route->rvalue == l_and && g_status)
			{	
				break;
			}
			else if (ast->node.route->rvalue == l_or && !g_status)
			{
				break;
			}
			new = new->node.route->next;
			if (!new)
				break;
			exit = min_executer(new->node.route->down, dict, build);	
	}		
	return (exit);
}	






	

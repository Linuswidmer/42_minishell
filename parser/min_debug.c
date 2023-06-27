/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:12:46 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/06/27 09:56:17 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*char *lexertype1_names[] =
{
    "EMPTY",
    "DQUOTE",
    "QUOTE",
    "WORD",
    "ASTERISK",
    "PAROPEN",
    "PARCLOSE",
    "HEREDOC",
    "APPEND",
    "IN",
    "OUT",
    "DOLLAR",
    "AND",
    "OR",
    "SEMI",
    "PIPE",
    "ESCAPE",
	"SPACE",
	"AMP"
	
};

char *lexertype2_names[] =
{
    "EMPTY",
    "DQUOTE",
    "QUOTE",
    "WORD",
    "*",
    "(",
    ")",
    "<< ",
    ">> ",
    "< ",
    "> ",
    "$",
    " && ",
    " || ",
    ";",
    " | ",
    "ESCAPE",
	" ",
	"&"
};	

char *nodetype_names[] =
{
    "ROUTENODE",
    "PIPENODE",
    "JOBNODE",
    "SUBNODE"
};


void  min_print_asterisk(t_expander *asterisk) 
{	
	int n;
	
	ft_printf_fd("*START ASTERISK\n", 2);
	n = 0;
	while (asterisk)
	{
		ft_printf_fd("NUMBER: %i, Lexertype: %s, Value: %s \n", 
		2, n++, lexertype1_names[asterisk->key], asterisk->word);   
		asterisk = asterisk->next;
	}
	ft_printf_fd("*END ASTERISK\n", 2);
}

void	min_print_jobnode(t_jobnode *job)
{
	//printf("JOBNODE: ");
	t_lexer *temp;

	temp = job->start;
	while (temp  != job->last)
	{
		if (temp->key == l_space)
			printf("%s", lexertype2_names[temp->key]);
		else
		 	printf("%s[%s] ", lexertype2_names[temp->key],  temp->value);
		temp = temp->next;
	}
	//printf("\n");
}	


void	min_print_subnode(char vt)
{
	//printf("SUBNODE: ");
	if (vt)
		printf(")");
	else
		printf("(");
	//printf("\n");

}	

void	min_print_pipenode(void)
{
	printf(" | ");
}


void	min_print_routenode(t_lexertype key)
{
	printf(" %s ", lexertype2_names[key]);
}


void min_print_ast(t_ast *ast)
{
	char	vt;
	char	ht;
	
	
	vt = 0;
	ht = 0;
	if (!ast)
		return;
	printf("START AST \n");
	while (1)
	{
		
//	printf("NODETYPE is: %s     \n", nodetype_names[ast->key]);
		if (ast->key == jobnode)
      	{
			min_print_jobnode(ast->node.job);
			vt = 1;
			if (ast->node.job->up)
				ast = ast->node.job->up;
            else
				break;
		}
        if (ast->key == subnode)
        {	
		min_print_subnode(vt);
	if (ast->node.sub->up && vt)
                ast = ast->node.sub->up;
	else if (!vt)
        	ast = ast->node.sub->down;       	
	else
		break;		
        }
        if (ast->key == pipenode)
        {
			if (vt && ast->node.pipe->next)
			{
				min_print_pipenode();
				ast = ast->node.pipe->next;
				vt = 0;
			}
			else if (!vt)
			{
                	ast = ast->node.pipe->down;
			}	
            		else 
			{
				while (ast->node.pipe->prev)
            				ast = ast->node.pipe->prev;
				if (ast->node.pipe->up)
					ast = ast->node.pipe->up;
				else
                			break;
			}
        }
        if (ast->key == routenode)
        {
			if (vt && ast->node.route->next)
            {
                min_print_routenode(ast->node.route->rvalue);
                ast = ast->node.route->next;
                vt = 0;
            }
            else if (!vt)
                ast = ast->node.route->down;
            else 
            {   
                while (ast->node.route->prev)
                    ast = ast->node.route->prev;
                if (ast->node.route->up)
                    ast = ast->node.route->up;
                else
                    break;
            }
		}
	}		
	printf("\nEND_AST\n\n");
}
*/
void	min_print_ast(t_ast *ast)
{
	(void)ast;
	ft_printf_fd("NO_DEBUG \n", 2);
}

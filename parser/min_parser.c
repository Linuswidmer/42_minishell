#include "parser.h"




int	ft_token_is_JOBNODE(t_lexertype key)
{
	if (min_is_IO(key) || min_is_WORD(key))
		return (1);
	else
		return (0);	 
}

int	ft_token_is_PIPENODE(t_lexertype key)
{
	if (key == PIPE)
		return (1);
	else 
		return(0);		
}

int	ft_token_is_ROUTENODE(t_lexertype key)
{
	if (min_is_PARA(key) || min_is_ROUTE(key))
		return (1);
	else
		return (0);
}

ft_bring_AST_to_beginning(void **ast)
{
	int a;

	a = 1;
	while (a)
	{
		if (*ast.key == JOBNODE && !*ast->up)
			a = 0;
		else if (*ast->up)
			*ast = *ast->up;
		else if (!*ast->last && !*ast->up)
			a = 0;		
		else if (*ast->last)
			*ast = *ast->last;
	}
}

/* PARSER MAIN*/
void	*min_parser(t_lexer *token)
{
	void *ast;
	while (token)
	{
		if (ft_token_is_JOBNODE(token->key)
			token =	min_JOBENODE(token, &ast);	
		else if (ft_token_is_PIPENODE(token->key)
			token = min_PIPENODE(token, &ast);
		else if (ft_token_is_ROUTENODE(token->key)			
			token = min_ROUTENODE(token, &ast);	
	}
	ft_bring_AST_to_begining(&ast);
	return (ast);
}

#include "parser.h"

/*
if (!ast)
			return (NULL);
		if (ast->key == jobnode)
			ast = ast->node.job->up;
		else if (ast->key == pipe && ast->node.pipe->prev)
			ast = ast->node.pipe->prev;
		else if (ast->key == pipe && !ast->node.pipe->prev)
			ast = ast->node.pipe->up;
		/* check if && route*/
		else if (ast->key == route && ast->node.route->prev
			ast = ast->node.route->prev;
		else if (ast->key == route && ast->node.route->rvalue is && || ;)
			 ast = 	ast->node.route->up;
		else if (ast->key == route && ast->node.route->rvalue is () && !first)
			return (ast);
		else if (ast->key == route && ast->node.route->rvalue is () && first)
			ast =  ast->node.route->up;
		ft_close_para(ast, 0);
}*



static t_ast	*ft_navigate_to_next_sub(t_ast *ast, char first)
{
	if (ast)		
	{
		if (ast->key == jobnode)
                	ast = ast->node.job->up;
        	else if (ast->key == subnode && first)
                	ast = ast->node.sub->up;
		else if (ast->key == pipe && ast->node.pipe->prev)
                        ast = ast->node.pipe->prev;
        	else if (ast->key == pipe && !ast->node.pipe->prev)
                        ast = ast->node.pipe->up;
		else if (ast->key == subnode  && !first)
                        return (ast);
		return (ft_navigate_to_next_sub(ast, 0));
       	}	
	return (ast);
}




static t_ast	*ft_close_para(t_ast **ast)
{
	t_ast **temp;

	if (!*ast || (*ast)->key == pipenode || (*ast)->key == routenode)
                min_parse_error(ast);
	else
	{
		temp = ast;
		*ast = ft_navigate_to_next_sub(*ast, 1);
		if (!*ast)
			min_parse_error(temp);
	}
	return (ast)
}


static t_ast	*ft_init_subnode(t_ast *up)
{
	t_ast   *sub; 

        sub = (t_ast *)malloc(sizeof(t_ast));
        if (!sub)
                return (NULL);
        ft_bzero(sub, sizeof(t_ast));
        sub->key = subnode;
        sub->node.sub = (t_subnode *)malloc(sizeof(t_subnode));
        if (!sub->node.sub)
                return (NUll);
        ft_bzero(sub->node.sub, sizeof(t_subnode));
        sub->node.sub->up = up;
        return (sub);



static t_ast  *ft_open_para(t_ast **ast)
{
	t_ast *temp;
	t_ast **old

	temp = *ast;
	old = ast;	
	*ast = ft_init_subnode(temp);
	if (!*ast)
	{
		min_parse_malloc_fail(old);	
		return (*ast)
	}	
	if (temp->key == subnode)
		(*old)->node.sub->down = *ast; 
	if (temp->key == pipenode)
		(*old)->node.pipe->down = *ast;
	if temp->key == routenode)
		(*old)->node.route->down = *ast;
	return (*ast);
}

/*
min_subnode	
		--> 1. if para_open -> new subnode get createtd;
		--> 2. if para_closed 	-> ceck parse error 
					-> move up to next subshell
		 return next token and clean total ast if any malloc failed or parse error.
*/
t_lexer *min_subnode(t_lexer *token, t_ast **ast)
{
	if (min_token_is_para() == 1)
		*ast = ft_open_para(ast);
	else
		*ast = ft_close_para(ast);
	return (token->next);
}

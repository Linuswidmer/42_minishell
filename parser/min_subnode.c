#include "parser.h"






   if ((*ast)->key == pipenode || (*ast)->key == routenode)
                min_Parse_error(ast);




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
        ft_bzero(job->node.job, sizeof(t_jobnode));
        job->node.job->up = up;
        return (job);



static t_ast  *ft_open_para(t_ast **ast)
{
	t_ast *temp;
	t_ast **old

	temp = *ast;
	old = ast;	
	*ast = ft_init_subnode(temp);
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
	if ((*ast)->key == pipenode || (*ast)->key == routenode)
                min_Parse_error(ast);
	else if (min_token_is_para() == 1)
		*ast = ft_open_para(ast);
	else
		*ast = ft_close_para(ast);
	return (token->next);
}

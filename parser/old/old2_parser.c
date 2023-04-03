include "parser.h"

void *last_node(void *node)
{
	while (node->next)
		node = node->next;
	return (node);
} 


void	init_ROUTENODE(t_ROUTENODE **ast)
{
	t_ROUTENODE *end;
	t_ROUTENODE *temp;	
	
	if (!*ast)
	{
		*ast = (t_ROUTENODE *)malloc(sizeof(t_ROUTENODE));		 	
		if (!*ast)
			min_free_ast(**ast);
		end = *ast;
		temp = NULL;		
	}
	else
	{
		end = last_node(*ast);
		temp = end; 
		end->next = (t_ROUTENODE *)malloc(sizeof(t_ROUTENODE));
		if (!end->next)
            min_free_ast(**ast);
		end = end->next;
	}
	ft_bzero(end, sizeof(t_ROUTENODE));
	end->last = temp
	end->under = (t_JOBNODE *)malloc(sizeof(t_JOBNODE));
	if (!end->under)
            min_free_ast(**ast);
	ft_bzero(end->under, sizeof(t_JOBNODE)); 
}


int is_quote(t_lexertype node)
{
	if	(node == DQUOTE || node == QUOTE)
			return (1);
	else
			return (0);
}

int is_IO(t_lexertype node)
{
		if	(node == HEREDOC || node == APPEND 
					|| node == IN || node == OUT) 
			return (1);
		else
			return (0);
}
*/
is_IN

is_OUT


void init_IO(t_lexer **data, void **ast)
{
		t_IONODE *end
			if (!*ast)
				
	
}
t_lexer *set_IO(t_lexer *data, void **ast) 
{
		void **temp;
		
		temp = ast;
		if (*ast->key == PIPENODE)
			*ast = *ast->right;		
		else if (*ast->key == ROUTENODE)
			*ast = *ast->under;
		if (is_IN(data->key)
			*ast = *ast->in
		else (is_OUT(data->key)
			*ast = *ast->out
		init_IO(&data, ast);
		ast =temp;
		return (data);
}
void	parser(t_lexer *data, t_ROUTENODE **ast)
{
		
	init_ROUTENODE(ast);	
	
	while (data)
	{
		if (is_quote(data->key)	
			data = data->next;
		else if (is_IO(data->key)
			data = set_IO(data, ast);
		else if (is_WORD(data->key)
			data = set_WORD(data, ast);
		else if (is_PIPE(data->key)
			data = set_PIPE(data, ast);
		else if (is_ROUTE(data->key)
			data = set_ROUTENODE(ast, data);
		}
}
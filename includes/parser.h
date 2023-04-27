/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:02:20 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/25 12:33:25 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H


/* FUNCTIONS */
t_ast	*min_parser(t_lexer *token); /* x */
void	min_parser_error(t_ast **ast, t_lexer *token);
void    min_parser_malloc_fail(t_ast **ast);
void	min_bring_ast_to_beginning(t_ast **ast);
void    min_free_ast(t_ast **ast);

/* ROUTE */
t_lexer *min_routenode(t_lexer *token,t_ast **ast);
int     min_token_is_route(t_lexertype key);

/* SUB */
int		min_token_is_para(t_lexertype key);
t_lexer *min_subnode(t_lexer *token, t_ast **ast);


/* PIPE */
t_lexer *min_pipenode(t_lexer *token, t_ast **ast);

/* JOBNODE */
t_lexer	*min_jobnode(t_lexer *token, t_ast **ast);

/* IO */
int			min_token_is_io(t_lexertype key); /*x*/
int			min_token_is_io_in(t_lexertype key);

/* WORD */
int     min_token_is_word(t_lexertype key);/*x*/
	
/* DEBUG */ 
void min_print_io(t_ionode *io);
void min_print_ast(t_ast *ast);
void    min_print_jobnode(t_jobnode *job);

/* HEREDOC*/
int min_heredoc(t_lexer **token, char *heredoc);
void	min_heredoc_fail(t_ast **ast);



#endif

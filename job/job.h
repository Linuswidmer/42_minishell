/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrotbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:45:11 by jstrotbe          #+#    #+#             */
/*   Updated: 2023/04/18 14:08:52 by jstrotbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H








char    **min_ex_get_cmd(t_cmdnode *cmd;

int     min_ex_io(t_ionode *io, char buildin);



/* common */
int     min_common_cmd(t_jobnode *astjob, t_dict *dict);


/* buildin */
int     min_buildin_cmd(t_jobnode *astjob, t_dict *dict, t_build *build);



/* job */
int     min_job(t_ast *ast, t_dict *dict, t_build *build  );

#endif


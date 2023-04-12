/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:28:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 16:36:14 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_dict {
    char *key;
    char *value;
    struct s_dict *next_entry;
}   t_dict;

typedef struct {
    int (*export)(t_dict*, char*);
    int (*cd)(char*);
} Commands;

typedef int (*builtin_ptr)(void**);

typedef struct {
    const char* name;
    builtin_ptr func;
} min_builtins;

void create_dict_on_startup(t_dict *var1, char **env);
void    print_dict(t_dict *dict);

int env(t_dict *dict);

int cd(char *arg);

int unset(t_dict **dict, char *arg);

int export(t_dict *dict, char *arg);
t_dict *search_key_in_dict(t_dict *var, char *arg);
t_dict *init_env_variable();
void write_to_env_variable(t_dict *var, char *key, char *value);


int export_wrapper(void** args);
int cd_wrapper(void** args);


#endif

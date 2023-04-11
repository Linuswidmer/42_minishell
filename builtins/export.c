/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:18:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/11 10:54:03 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	**ft_split(char const *s, char c);

typedef struct s_env_variable {
	char *key;
	char *value;
	struct s_env_variable *next_var;
}	t_env_variable;


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (ft_strlen(src));
	else
	{
		while (index < (size - 1) && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
		return (ft_strlen(src));
	}
}

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}

t_env_variable *create_env_variable(char *key, char *value)
{
	t_env_variable *var;

	var = malloc(sizeof(t_env_variable));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->next_var = NULL;
	return (var);
}

int main(int argc, char **argv, char **env)
{
	int i;
	t_env_variable *var;
	t_env_variable *var1;
	t_env_variable *var2;

	var1 = create_env_variable("num", "1000");
	var2 = create_env_variable("num2", "2000");
	var1->next_var = var2;
	i = 0;

	while (env[i])
	{
	printf("%s\n", env[i]);	
	i ++;
	}
	var = var1;
	//while (var)
	//{
	//	printf("Key is %s	Value is %s	\n", var->key, var->value);
	//	var = var->next_var;
	//}
}

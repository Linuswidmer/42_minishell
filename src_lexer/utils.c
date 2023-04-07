/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:53:03 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/04 12:55:22 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (8);
	else
		return (0);
}

size_t  ft_strlen(const char *str)
{
    size_t  i;  

    i = 0;
    if (!str)
        return (i);
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

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < n)
		{
			((char *)s)[i] = '\0';
			i++;
		}
	}
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmeb > 2147483647 / size)
		return (0);
	if (nmeb != 0 && size > 2147483647 / nmeb)
		return (0);
	ptr = malloc(nmeb * size);
	if (ptr)
	{
		ft_bzero(ptr, nmeb * size);
		return (ptr);
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (start >= ft_strlen(s))
	{
		ptr = ft_calloc(1, 1);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (len + start > ft_strlen(s))
	{
		ptr = ft_calloc(ft_strlen(s) + 1 - start, 1);
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr, s + start, ft_strlen(s) + 1 - start);
	}
	else
	{
		ptr = ft_calloc(len + 1, 1);
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr, s + start, len + 1);
	}
	return (ptr);
}

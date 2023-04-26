#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>         
#include <unistd.h>


size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (s1[i] != '\0' && s2[i] != '\0'
			&& i <= n - 1 && s1[i] == s2[i])
			i++;
		if (i == n)
			return ((unsigned char)s1[i - 1] -(unsigned char)s2[i - 1]);
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
		return (0);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	size_t	s1l;
	size_t	s2l;
	size_t	i1;
	size_t	i2;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	i1 = 0;
	i2 = 0;
	nstr = (char *)malloc(sizeof(char) * (s1l + s2l + 1));
	if (!nstr)
		return (NULL);
	while (i1 < s1l)
		nstr[i1++] = *s1++;
	while (i2 < s2l)
		nstr[i1 + i2++] = *s2++;
	if (!s1l && !s2l)
		nstr[0] = '\0';
	else
		nstr[i1 + i2] = '\0';
	return (nstr);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nstr;
	size_t	i;
	size_t	ls;

	if (!s)
		return (NULL);
	i = 0;
	ls = ft_strlen(s);
	if (len > ls)
		len = ls;
	if (start > ls)
		len = 0;
	if (start == ls - 1 && len)
		len = 1;
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (NULL);
	if (start < ls)
	{
		while (s[start] && i < len)
			nstr[i++] = s[start++];
	}
	nstr[i] = '\0';
	return (nstr);
}



static int	ft_cins(char const *ws, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (ws[++i])
	{
		if (ws[i] == c && i > 0)
			if (ws[i - 1] != c)
				count++;
	}
	if (ft_strlen(ws) && ws[i - 1] != c)
		count++;
	return (count);
}

static void	ft_freeall(char	**rs, int irs)
{
	while (irs > 0)
		free(rs[irs--]);
	if (irs == 0)
		free(rs[irs]);
	free(rs);
}

static size_t	ft_lenword(char *ws, unsigned int start, char c)
{
	size_t	lword;

	lword = 0;
	while (ws[start + lword] != c && ws[start + lword])
		lword++;
	return (lword);
}

static char	**ft_into(char **rs, char *ws, char c)
{
	int				irs;
	unsigned int	start;
	size_t			end;

	end = 0;
	start = 0;
	irs = 0;
	while (ws[start])
	{
		end = ft_lenword(ws, start, c);
		if (end)
		{
			rs[irs] = ft_substr(ws, start, end);
			if (!rs[irs++])
			{
				ft_freeall(rs, irs - 2);
				return (NULL);
			}
			start = start + end;
		}
		else
			start++;
	}
	rs[irs] = NULL;
	return (rs);
}

char	**ft_split(char const *s, char c)
{
	int		cins;
	char	**rs;
	char	*ws;

	ws = (char *)s;
	cins = ft_cins(ws, c);
	rs = (char **)malloc((sizeof(char *) * (cins + 1)));
	if (!rs)
		return (0);
	if (cins)
		return (ft_into(rs, ws, c));
	else
	{
		rs[cins] = NULL;
		return (rs);
	}
}


char **ft_init_path(char *envp[])
{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			paths = ft_split(((*envp) + 5), ':');
		envp++;
	}
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		//gnl_free(&paths[i]);
		paths[i++] = temp;
	}
	return (paths);
}

static char *ft_checkpath(char **paths, char *cmd)
{
	int	i;
	char *path; 
	
	if (!paths)
		return (NULL);
	i = 0;
	path = ft_strjoin(paths[i], cmd);
	//printf ("%s", path);
	while (paths[i])
	{	
		if (!access(path, F_OK))
			return (path);
		if (paths[++i])
		{
			free(path);
			path = NULL;
			path = ft_strjoin(paths[i], cmd);
		}
	}
	return (NULL);
}




int main (int argc, char *argv[], char	*envp[])
{

	int i; 
	char *path; 
	if (argc != 2)
		return (1);
		
	path = ft_checkpath(ft_init_path(envp), argv[1]);
	printf("%s\n", path);
	free(path);
	return (0);
}

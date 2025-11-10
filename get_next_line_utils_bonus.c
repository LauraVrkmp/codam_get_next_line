/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: laveerka <laveerka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/19 20:06:56 by laveerka      #+#    #+#                 */
/*   Updated: 2025/11/10 15:52:42 by laveerka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **stash, char *line, char *temp)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (line)
		free(line);
	if (temp)
		free(temp);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	char	*start;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	start = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (start);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && *src)
		{
			*dst++ = *src++;
			i++;
		}
		*dst = '\0';
	}
	while (*src++)
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_strchri(const char *s, int c)
{
	unsigned char	ch;
	int				i;

	i = 0;
	ch = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (ch == '\0')
		return (i);
	return (-1);
}

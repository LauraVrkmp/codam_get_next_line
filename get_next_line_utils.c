/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: laveerka <laveerka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/19 20:06:56 by laveerka      #+#    #+#                 */
/*   Updated: 2025/11/04 12:43:23 by laveerka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

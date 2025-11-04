/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laveerka <laveerka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/19 20:06:50 by laveerka      #+#    #+#                 */
/*   Updated: 2025/11/04 13:24:14 by laveerka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(char *stash, int fd, int factor, int *bytesRead)
{
	*bytesRead = read(fd, stash, factor * BUFFER_SIZE);
	stash[*bytesRead] = '\0';
	return (stash);
}

static char	*extract_line(char *stash)
{
	int		nl_loc;
	char	*line;

	nl_loc = ft_strchri(stash, '\n');
	if (nl_loc < 0)
		nl_loc = ft_strchri(stash, '\0');
	line = malloc(sizeof(char) * (nl_loc + 1));
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	ft_strlcpy(line, stash, nl_loc);
	return (line);
}

static char *next_line(char *stash)
{
	int	nl_loc;

	nl_loc = ft_strchri(stash, '\n');
	if (nl_loc < 0)
		return (stash);
	ft_strlcpy(stash, stash + nl_loc, ft_strlen(stash) - ft_strlen(stash + nl_loc));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*new_stash;
	char		*line;
	int			factor;
	int			*bytesRead;

	factor = 1;
	bytesRead = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (stash == NULL)
			return (NULL);
	}
	stash = read_line(stash, fd, factor, bytesRead);
	while (ft_strchri(stash, '\n') < 0 || ft_strchri(stash, '\0') != bytesRead)
	{
		factor *= 2;
		new_stash = malloc(sizeof(char) * (factor * BUFFER_SIZE + 1));
		if (new_stash == NULL)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		ft_strlcpy(new_stash, stash, ft_strlen(stash));
		bytesRead = 0;
		new_stash = read_line(new_stash + ft_strlen(stash), fd, factor, bytesRead);
		free(stash);
		stash = new_stash;
	}
	line = extract_line(stash);
	if (line == NULL)
		return (NULL);
	stash = next_line(stash);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text_small.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
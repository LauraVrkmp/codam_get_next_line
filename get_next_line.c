/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laveerka <laveerka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/19 20:06:50 by laveerka      #+#    #+#                 */
/*   Updated: 2025/11/07 13:01:01 by laveerka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(char *stash, int fd, int *bytesRead)
{
	int		stash_length;
	char	*new_stash;
	char	*temp;

	stash_length = ft_strlen(stash);
	if (stash_length == 0)
	{
		*bytesRead = read(fd, stash, BUFFER_SIZE);
		stash[*bytesRead] = '\0';
	}
	else
	{
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (temp == NULL)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		*bytesRead = read(fd, temp, BUFFER_SIZE);
		temp[*bytesRead] = '\0';
		new_stash = ft_strjoin(stash, temp);
		free(stash);
		free(temp);
		stash = new_stash;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	int		nl_loc;
	int		nl_null;
	char	*line;

	if (stash == NULL)
		return (NULL);
	nl_loc = ft_strchri(stash, '\n');
	if (nl_loc < 0)
	{
		nl_loc = ft_strchri(stash, '\0');
		nl_null = 1;
	}
	else
		nl_null = 2;
	line = malloc(sizeof(char) * (nl_loc + nl_null));
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	ft_strlcpy(line, stash, nl_loc + nl_null);
	return (line);
}

static char *next_line(char *stash)
{
	int		nl_loc;
	char	*new;
	int		i;

	i = 0;
	nl_loc = ft_strchri(stash, '\n');
	if (nl_loc < 0)
	{
		free(stash);
		return (NULL);
	}
	nl_loc++;
	new = malloc(sizeof(char) * (ft_strlen(stash + nl_loc) + 1));
	if (new == NULL)
	{
		free(stash);
		return (NULL);
	}
	while (stash[nl_loc])
		new[i++] = stash[nl_loc++];
	new[i] = '\0';
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytesRead;

	bytesRead = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (stash == NULL)
			return (NULL);
		stash[0] = '\0';
	}
	while (ft_strchri(stash, '\n') < 0 && bytesRead == BUFFER_SIZE)
	{
		stash = read_line(stash, fd, &bytesRead);
		if (stash == NULL)
			return (NULL);
	}
	line = extract_line(stash);
	stash = next_line(stash);
	if (stash == NULL && (line == NULL || line[0] == '\0'))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("text_small.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}
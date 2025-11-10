/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laveerka <laveerka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/19 20:06:50 by laveerka      #+#    #+#                 */
/*   Updated: 2025/11/10 10:29:25 by laveerka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(char *stash, int fd, int *bytesRead)
{
	char	*new_stash;
	char	*temp;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	*bytesRead = read(fd, temp, BUFFER_SIZE);
	if (*bytesRead < 0)
	{
		free(stash);
		stash = NULL;
		free(temp);
		return (NULL);
	}
	temp[*bytesRead] = '\0';
	new_stash = ft_strjoin(stash, temp);
	free(stash);
	free(temp);
	if (new_stash == NULL)
		return (NULL);
	stash = new_stash;
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
		return (NULL);
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
		if (stash)
			free(stash);
		return (NULL);
	}
	nl_loc++;
	new = malloc(sizeof(char) * (ft_strlen(stash + nl_loc) + 1));
	if (new == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	while (stash[nl_loc])
		new[i++] = stash[nl_loc++];
	new[i] = '\0';
	free(stash);
	if (new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytesRead;

	bytesRead = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	if (stash == NULL)
	{
		stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (stash == NULL)
			return (NULL);
		stash[0] = '\0';
	}
	while (bytesRead > 0)
	{
		stash = read_line(stash, fd, &bytesRead);
		if (stash == NULL)
			return (NULL);
		if (bytesRead == 0 || ft_strchri(stash, '\n') >= 0)
			break ;
	}
	line = extract_line(stash);
	if (line == NULL)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	stash = next_line(stash);
	if (stash && stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
	}
	if (stash == NULL && (line == NULL || line[0] == '\0'))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("text.txt", O_RDONLY);
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
} */
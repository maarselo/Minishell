/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:39:34 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/02/05 22:39:34 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_addstr(char **stored, char *buffer)
{
	size_t	oldlen;
	size_t	newlen;
	char	*newbuffer;
	size_t	i;

	if (!*stored)
		*stored = ft_strdup("");
	oldlen = ft_strlen(*stored);
	newlen = oldlen + ft_strlen(buffer) + 1;
	newbuffer = malloc(newlen);
	if (!newbuffer)
		return ;
	i = 0;
	while ((*stored)[i] != '\0')
	{
		newbuffer[i] = (*stored)[i];
		i++;
	}
	newbuffer[i] = '\0';
	ft_strcat(newbuffer, buffer);
	free(*stored);
	*stored = newbuffer;
}

char	*ft_getline(char **stored)
{
	char	*nlpos;
	char	*newstored;
	char	*line;
	size_t	len;

	if (!*stored || !**stored)
		return (NULL);
	nlpos = ft_strchr(*stored, '\n');
	if (!nlpos)
	{
		line = *stored;
		*stored = NULL;
		return (line);
	}
	len = nlpos - *stored + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, *stored, len);
	line[len] = '\0';
	newstored = ft_strdup(nlpos + 1);
	free(*stored);
	*stored = newstored;
	return (line);
}

void	ft_read(int fd, char **stored)
{
	ssize_t		bytesread;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	bytesread = read(fd, buffer, BUFFER_SIZE);
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		ft_addstr(stored, buffer);
		if (!*stored)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
		bytesread = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytesread == -1)
	{
		free(*stored);
		*stored = NULL;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read(fd, &stored);
	if (!stored || !*stored)
	{
		free(stored);
		stored = NULL;
		return (NULL);
	}
	line = ft_getline(&stored);
	return (line);
}

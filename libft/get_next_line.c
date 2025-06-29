/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:54:46 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/29 13:54:48 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_buffjoin(char **buffer, char *tmp_buffer)
{
	char	*tmp;

	if (!buffer || !tmp_buffer)
		return ;
	tmp = *buffer;
	*buffer = ft_strjoin(*buffer, tmp_buffer);
	free(tmp);
}

static char	*ft_getline(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (ft_substr(buffer, 0, i));
}

static void	ft_nextline(char **buffer)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	if (!*buffer)
		return ;
	i = 0;
	tmp = *buffer;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	len = ft_strlen(*buffer);
	*buffer = ft_substr(*buffer, i, len - i);
	free(tmp);
}

static void	ft_read(int fd, char **buffer)
{
	ssize_t	bytes_read;
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buffer)
		return ;
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(tmp_buffer, '\n'))
	{
		bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(tmp_buffer);
			return ;
		}
		tmp_buffer[bytes_read] = '\0';
		ft_buffjoin(buffer, tmp_buffer);
		if (!*buffer)
		{
			free(tmp_buffer);
			return ;
		}
	}
	free(tmp_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read(fd, &buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_getline(buffer);
	if (!line)
		free(buffer);
	ft_nextline(&buffer);
	return (line);
}

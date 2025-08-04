/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:33:23 by fleite-j          #+#    #+#             */
/*   Updated: 2024/11/29 19:25:13 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*ft_fill_line_buffer(int fd, char *buffer, char *stored_buffer)
{
	ssize_t	bytes_read;
	char	*temporary_buffer;

	bytes_read = 1;
	temporary_buffer = NULL;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stored_buffer)
			stored_buffer = ft_strdup("");
		temporary_buffer = stored_buffer;
		stored_buffer = ft_strjoin(temporary_buffer, buffer);
		free(temporary_buffer);
		temporary_buffer = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stored_buffer);
}

static char	*ft_set_line(char *line)
{
	int		end_of_line;
	char	*remaining_data;
	char	*new_line;

	if (line && ft_strchr(line, '\n'))
	{
		new_line = ft_strchr(line, '\n');
		end_of_line = ft_strlen(line) - ft_strlen(new_line) + 1;
		remaining_data = ft_strdup(new_line + 1);
		line[end_of_line] = '\0';
		return (remaining_data);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stored_buffer;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_fill_line_buffer(fd, buffer, stored_buffer);
	free(buffer);
	if (line == NULL && stored_buffer)
		free (stored_buffer);
	stored_buffer = ft_set_line(line);
	if (line == NULL || *line == '\0')
	{
		free (line);
		line = NULL;
	}
	return (line);
}

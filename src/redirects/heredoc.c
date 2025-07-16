/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_file(void)
{
	int		i;
	char	*temp_file;
	char	*nbr_file;

	i = 0;
	while (6)
	{
		nbr_file = ft_itoa(i);
		if (!nbr_file)
			return (NULL);
		temp_file = ft_strjoin("/tmp/minishell_heredoc_", nbr_file);
		free(nbr_file);
		if (!temp_file)
			return (NULL);
		if (access(temp_file, F_OK) != 0)
			return (temp_file);
		free(temp_file);
		i++;
	}
}

static int	write_till_delimiter(int fd, char *delimiter, t_minishell *sh)
{
	char	*line;
	char	*expanded;

	while (6)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			return (0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (1);
		}
		expanded = replace_variables(sh, line);
		free(line);
		if (!expanded)
			return (0);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	return (0);
}

int	handle_heredoc(t_redirect *redir, t_minishell *sh)
{
	int		fd;
	char	*temp_file;

	temp_file = generate_file();
	if (!temp_file)
		return (0);
	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(temp_file);
		return (0);
	}
	if (!write_till_delimiter(fd, redir->filename, sh))
	{
		close(fd);
		unlink(temp_file);
		free(temp_file);
		return (0);
	}
	close(fd);
	free(redir->filename);
	redir->filename = temp_file;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/08/01 20:45:40 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line_from_stdin(void)
{
	char	buffer[1024];
	char	*line;
	int		len;

	if (!fgets(buffer, sizeof(buffer), stdin))
		return (NULL);
	len = ft_strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

int	write_till_delimiter(int fd, char *delimiter, t_minishell *sh)
{
	char	*line;
	char	*expanded;

	while (6)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = read_line_from_stdin();
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			return (1);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (1);
		}
		expanded = expanded_variable(line, sh);
		free(line);
		if (!expanded)
			return (0);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}

void	handle_child_routine(const char *delimiter, \
			int write_fd, t_minishell *sh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (!write_till_delimiter(write_fd, (char *)delimiter, sh))
	{
		close(write_fd);
		free((void *)delimiter);
		cleanup_child_before_exit(sh, 1);
	}
	close(write_fd);
	cleanup_child_before_exit(sh, 0);
}

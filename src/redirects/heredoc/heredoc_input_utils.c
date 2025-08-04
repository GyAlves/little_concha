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

static char	*read_heredoc_line(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("> ");
	else
		line = get_next_line(STDIN_FILENO);
	return (line);
}

static int	process_heredoc_line(char *line, char *del, int fd, t_minishell *sh)
{
	char	*expanded;

	if (ft_strcmp(line, del) == 0)
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
	return (2);
}

int	write_till_delimiter(int fd, char *delimiter, t_minishell *sh)
{
	char	*line;
	int		status;

	while (1)
	{
		line = read_heredoc_line();
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			return (1);
		}
		status = process_heredoc_line(line, delimiter, fd, sh);
		if (status == 1)
			return (1);
		if (status == 0)
			return (0);
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	cleanup_child_before_exit(shell_cmd(), 130);
}

void	handle_child_routine(const char *delimiter, \
			int write_fd, t_minishell *sh)
{
	signal(SIGINT, sigint_handler);
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

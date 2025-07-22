/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_till_delimiter(int fd, char *delimiter, t_minishell *sh)
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
}

void	handle_child_routine(const char *delimiter, \
			int write_fd, t_minishell *sh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(STDIN_FILENO);
	if (dup2(sh->original_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 original_stdin failed in heredoc child");
		close(write_fd);
		exit(1);
	}
	if (!write_till_delimiter(write_fd, (char *)delimiter, sh))
	{
		close(write_fd);
		exit(1);
	}
	close(write_fd);
	exit(0);
}

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

int	handle_heredoc(t_redirect *redir, t_minishell *sh)
{
	int	fd;
	int	heredoc_success;

	redir->heredoc_delimiter = ft_strdup(redir->filename);
	if (!redir->heredoc_delimiter)
	{
		perror("minishell: strdup failed for heredoc delimiter");
		return (0);
	}
	fd = heredoc_init_file(redir);
	if (fd == -1)
	{
		free(redir->heredoc_delimiter);
		redir->heredoc_delimiter = NULL;
		return (0);
	}
	heredoc_success = handle_heredoc_fork_n_wait(fd, sh, redir);
	free(redir->heredoc_delimiter);
	redir->heredoc_delimiter = NULL;
	return (heredoc_success);
}

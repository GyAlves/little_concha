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

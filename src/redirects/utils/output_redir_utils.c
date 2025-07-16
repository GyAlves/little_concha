/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	output_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}*/

int  output_redir(t_redirect *redir)
{
    int fd;

    dprintf(2, "CHILD %d (R_OUT): Opening %s with O_TRUNC\n", getpid(), redir->filename);
    fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("output_redir open failed");
        return (0);
    }
    dprintf(2, "CHILD %d (R_OUT): Opened FD: %d\n", getpid(), fd);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("output_redir dup2 failed");
        close(fd);
        return (0);
    }
    dprintf(2, "CHILD %d (R_OUT): STDOUT_FILENO after dup2 for file: %d (fd of /proc/self/fd/1)\n", getpid(), fcntl(STDOUT_FILENO, F_GETFD));
    close(fd);
    return (1);
}

int	append_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

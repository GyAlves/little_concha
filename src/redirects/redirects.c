#include "../../minishell.h"

int	apply_redir(t_redirect *redir)
{
	int	fd;

	if (redir->type == R_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == R_IN)
		fd = open(redir->filename, O_RDONLY);
	else
		return (0);
	if (fd < 0)
		return (0);
	if (redir->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

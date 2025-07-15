#include "minishell.h"

static int	input_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

static int	output_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	append_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	heredoc_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	apply_redir(t_redirect *redir)
{
	if (redir->type == R_IN)
		return (input_redir(redir));
	else if (redir->type == R_OUT)
		return (output_redir(redir));
	else if (redir->type == APPEND)
		return (append_redir(redir));
	else if (redir->type == HEREDOC)
		return (heredoc_redir(redir));
	return (0);
}

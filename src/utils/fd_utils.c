#include "../../minishell.h"

void	save_std_backup(t_std_redir *backup, t_redirect *redir)
{
	if (redir->type == R_IN)
		backup->in = dup(STDIN_FILENO);
	else if (redir->type == R_OUT || redir->type == APPEND)
		backup->out = dup(STDOUT_FILENO);
}

void	restore_std_backup(t_std_redir *backup)
{
	if (backup->in != -1)
	{
		dup2(backup->in, STDIN_FILENO);
		close(backup->in);
		backup->in = -1;
	}
	if (backup->out != -1)
	{
		dup2(backup->out, STDOUT_FILENO);
		close(backup->out);
		backup->out = -1;
	}
}

t_redir_type	get_redir_type(char *str)
{
	if (!str)
		return (INVALID);
	if (ft_strcmp(str, ">") == 0)
		return (R_OUT);
	else if (ft_strcmp(str, "<") == 0)
		return (R_IN);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	return (INVALID);
}

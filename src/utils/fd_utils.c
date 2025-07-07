#include "../../minishell.h"

void	save_std_backup(t_std_redir *backup, t_redirect *redir)
{
	if (redir->type == R_IN || redir->type == HEREDOC)
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

#include "../../minishell.h"

char	**read_input(char **prompt)
{
	*prompt = readline("type> ");
	if (!*prompt || **prompt == '\0')
	{
		if (*prompt)
			free(*prompt);
		return (NULL);
	}
	add_history(*prompt);
	return (lexer(*prompt));
}

static int	process_single_redir(t_redirect *redir, t_minishell \
	*sh, t_std_redir *backup)
{
	if (redir->type == HEREDOC)
		return (handle_heredoc(redir, sh));
	save_std_backup(backup, redir);
	if (!apply_redir(redir))
		return (0);
	return (1);
}

static int	handle_redir_in_exc(t_minishell \
	*sh, t_command *cmd, t_std_redir *backup)
{
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (!process_single_redir(&cmd->redirects[i], sh, backup))
		{
			sh->exit_status = 1;
			restore_std_backup(backup);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_n_exc_cmd(t_minishell *sh, t_command *cmd, char **args, char *prompt)
{
	int			status;
	t_std_redir	backup;

	backup.in = -1;
	backup.out = -1;
	if (!parse_n_init_cmd(sh, cmd, args))
		return (1);
	if (!handle_redir_in_exc(sh, cmd, &backup))
		return (1);
	if (is_builtin(cmd))
		status = dispatch_builtin(sh, cmd, prompt);
	else
	{
		exec_cmd(sh, cmd);
		status = sh->exit_status;
	}
	restore_std_backup(&backup);
	return (status);
}

#include "../../minishell.h"

char	**read_input(char **prompt)
{
	*prompt = readline("type> ");
	if (!*prompt)
		return (NULL);
	add_history(*prompt);
	return (lexer(*prompt));
}

static void	restore_std(int in, int out)
{
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

int	init_n_exc_cmd(t_minishell *sh, t_command *cmd, char **args, char *prompt)
{
	int	i;
	int	status;
	int	std_in_save;
	int	std_out_save;

	std_in_save = -1;
	std_out_save = -1;
	if (!parse_cmd(sh, cmd, args))
		return (1);
	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strcmp(cmd->redirects[i].type, "<") == 0 && std_in_save == -1)
			std_in_save = dup(STDIN_FILENO);
		else if (ft_strcmp(cmd->redirects[i].type, ">") == 0 && \
			std_out_save == -1)
			std_out_save = dup(STDOUT_FILENO);
		if (!apply_redir(&cmd->redirects[i]))
		{
			sh->exit_status = 1;
			return (1);
		}
		i++;
	}
	if (is_builtin(cmd))
		status = dispatch_builtin(sh, cmd, prompt);
	else
	{
		exec_cmd(sh, cmd);
		status = sh->exit_status;
	}
	restore_std(std_in_save, std_out_save);
	return (status);
}

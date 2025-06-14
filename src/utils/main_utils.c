#include "../../minishell.h"

static int		dispatch_builtin(t_minishell *ms, t_command *cmd, char *prompt)
{
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		builtin_env(ms, cmd);
		return (0);
	}	
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		bi_echo(ms, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		bi_exit(ms, cmd, prompt);
		return (-1);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		bi_pwd(ms);
		return (0);
	}
	return (0);
}

int	init_n_exc_cmd(t_minishell *ms, t_command *cmd, char **args, char *prompt)
{
	int	status;

	cmd->args = args;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->piped = 0;
	cmd->append = 0;
	if (is_builtin(cmd))
		status = dispatch_builtin(ms, cmd, prompt);
	else
	{
		exec_cmd(ms, cmd);
		status = 0;
	}
	return (status);
}

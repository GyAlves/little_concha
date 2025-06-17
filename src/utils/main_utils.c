#include "../../minishell.h"

char	**read_input(char **prompt)
{
	char	**args;

	*prompt = readline("type> ");
	if (!*prompt)
		return (NULL);
	add_history(*prompt);
	args = ft_split(*prompt, ' ');
	return (args);
}

static int	dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt)
{
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		bi_env(sh, cmd);
		return (0);
	}	
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		bi_echo(sh, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		bi_exit(sh, cmd, prompt);
		return (-1);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		bi_pwd(sh);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
	{
		bi_cd(sh, cmd);
		return (0);
	}
	return (0);
}

int	init_n_exc_cmd(t_minishell *sh, t_command *cmd, char **args, char *prompt)
{
	int	status;

	cmd->args = args;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->piped = 0;
	cmd->append = 0;
	if (is_builtin(cmd))
		status = dispatch_builtin(sh, cmd, prompt);
	else
	{
		exec_cmd(sh, cmd);
		status = sh->exit_status;
	}
	return (status);
}

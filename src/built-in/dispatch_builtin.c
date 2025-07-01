#include "../../minishell.h"

static int	bi_from_cd_until_exit(t_minishell *sh, \
	t_command *cmd, char *prompt)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
	{
		bi_cd(sh, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		bi_echo(sh, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		bi_env(sh, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		bi_exit(sh, cmd, prompt);
		return (-1);
	}
	return (1);
}

static int	bi_from_export_until_unset(t_minishell *sh, t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
	{
		bi_export(sh, cmd);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		bi_pwd(sh);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
	{
		bi_unset(sh, cmd);
		return (0);
	}
	return (1);
}

int	is_builtin(t_command *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	return (0);
}

int	dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt)
{
	int	return_val;

	return_val = bi_from_cd_until_exit(sh, cmd, prompt);
	if (return_val <= 0)
		return (return_val);
	return_val = bi_from_export_until_unset(sh, cmd);
	if (return_val == 0)
		return (0);
	return (1);
}

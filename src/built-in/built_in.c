#include "../minishell.h"

void	builtin_env(t_minishell *ms, t_command *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		print_cmd_err(cmd->args[1]);
		ms->exit_status = 127;
		return ;
	}
	i = 0;
	while (ms->envp[i])
	{
		write(1, ms->envp[i], ft_strlen(ms->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	ms->exit_status = 0;
}

int is_builtin(t_command *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (1);
	return (0);
}
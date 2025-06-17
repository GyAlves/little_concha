#include "../../minishell.h"

int is_builtin(t_command *cmd)
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
	return (0);
}

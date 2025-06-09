#include "../minishell.h"

void	find_path(t_command cmd)
{
	if (ft_strchr(cmd.args[0], '/'))
	{
		if (access(cmd.args[0], X_OK))
			execvp(cmd.args[0], cmd.args);
	}
	else
		perror("cmd not found");
}
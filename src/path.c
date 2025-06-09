#include "../minishell.h"

char	*find_path(char *cmd)
{
	char	**path;

	path = get_path();
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else if (access(cmd[0], X_OK) == -1)
			return (NULL);
	}
	else
		get_path();
	return (cmd);
}

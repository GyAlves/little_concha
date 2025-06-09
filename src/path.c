#include "../minishell.h"

char	*find_path(char *cmd)
{
	char	**path;
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
			return (execvp(cmd[0], cmd));
		else if (access(cmd[0], X_OK) == -1)
		{
			//perror("minishell: cmd not found");
			return (NULL);
		}
	}
	else
		get_path();
	path = envar_handler(cmd);
	return (path);
}
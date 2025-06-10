#include "../minishell.h"

char	*find_path(char *cmd)
{
	int		i;
	char	**path;
	char	*dir;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else if (access(cmd, X_OK) == -1)
		{
			perror("not executable!\n");
			return (NULL);
		}
	}
	else
	{
		i = 0;
		path = get_path();
		while (path[i])
		{
			dir = ft_strjoin(path[i], "/");
			full_path = ft_strjoin(dir, cmd);
			free(dir);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(path);
			free(full_path);
			i++;
		}
	}
	return (NULL);
}

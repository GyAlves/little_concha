#include "../minishell.h"

char	*find_path(char *cmd)
{
	int		i;
	char	**path;
	char	*dir;
	char	*full_path;

	path = get_path();
	cmd = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
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
			{
				free(path);
				return (full_path);
			}
			free(full_path);
			i++;
		}
	}
	while (path)
		free(path);
	return (cmd);
}

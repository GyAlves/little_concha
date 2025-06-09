#include "../minishell.h"

char	*find_path(char *cmd)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*dir;
	char	*full_path;
	char	*tmp_path;

	path = get_path();
	cmd = NULL;
	if (ft_strchr(cmd, '/'))
	{
		tmp = ft_strjoin(dir, '/');
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else if (access(cmd, X_OK) == -1)
			return (NULL);
	}
	else
	{
		i = 0;
		path = get_path();
		while (path[i])
		{
			tmp_path = ft_strjoin(path[i], "/");
			full_path = ft_strjoin(tmp_path, cmd);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			else
			{
				free(full_path);
				free(dir);
			}
			i++;
		}
	}
	while (path)
		free(path);
	if (!path)
		return (NULL);
	return (cmd);
}

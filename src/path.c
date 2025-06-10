#include "../minishell.h"

char	**get_path(void)
{
	char 	*path;
	char	**envar_path;

	path = getenv("PATH");
	if (path == NULL)
	{
		envar_path = ft_calloc(3, sizeof(char *));
		if (!envar_path)
			return (NULL);
		envar_path[0] = ft_strdup("/bin");
		if (!envar_path[0])
		{
			free(envar_path);
			return (NULL);
		}
		envar_path[1] = ft_strdup("/usr/bin");
		if (!envar_path[1])
		{
			free(envar_path[0]);
			free(envar_path);
			return (NULL);
		}
		envar_path[2] = NULL;
	}
	else
	{
		envar_path = ft_split(path, ':');
		if (!envar_path)
			return (NULL);
	}
	return (envar_path);
}

char	*find_path(char *cmd)
{
	int		i;
	int		j;
	char	**path;
	char	*dir;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else if (access(cmd, X_OK) != 0)
			return (NULL);
	}
	else
	{
		i = 0;
		path = get_path();
		while (path[i])
		{
			j = 0;
			dir = ft_strjoin(path[i], "/");
			if (!dir)
			{
				free(path[i]);
				return (NULL);
			}
			full_path = ft_strjoin(dir, cmd);
			free(dir);
			if (!full_path)
			{
				free(path[i]);
				return (NULL);
			}
			if (access(full_path, X_OK) == 0)
			{
				free(path[i]);
				return (full_path);
			}
			free(full_path);
			i++;
			j++;
		}
		free(path[j]);
	}
	return (NULL);
}

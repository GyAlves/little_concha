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
	char	**path;
	char	*dir;
	char	*full_path;

	if (ft_strchr(cmd, '/')) //could be absolute or relative
	{
		if (access(cmd, X_OK) == 0)
			return (cmd); //is executable
		return (NULL); //exists but is not executable
	}
	
	path = get_path(); //simple cmd without '/', to find the folder in PATH
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		dir = ft_strjoin(path[i], "/");
		if (!dir)
		{
			free_matrix(path);
			return (NULL);
		}
		full_path = ft_strjoin(dir, cmd);
		free(dir);
		if (!full_path)
		{
			free_matrix(path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_matrix(path);
			return (full_path); //cmd found and is executable
		}
		free(full_path);
		i++;
	}
	free_matrix(path);
	return (NULL); //no path found
}

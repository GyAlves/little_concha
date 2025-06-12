#include "../minishell.h"

static char	**def_path(void)
{
	char	**path;

	path = ft_calloc(3, sizeof(char *));
	if (!path)
		return (NULL);
	path[0] = ft_strdup("/bin");
	if (!path[0])
	{
		free(path);
		return (NULL);
	}
	path[1] = ft_strdup("/usr/bin");
	if (!path[1])
	{
		free(path[0]);
		free(path);
		return (NULL);
	}
	path[2] = NULL;
	return (path);
}

char	**get_envar_path(void)
{
	char	*path;
	char	**envar_path;

	path = getenv("PATH");
	if (path == NULL)
		return (def_path());
	envar_path = ft_split(path, ':');
		if (!envar_path)
			return (NULL);
	return (envar_path);
}

static char	*build_and_check_path(char *cmd, char *path_dir)
{
	char	*dir_path;
	char	*full_path;

	dir_path = ft_strjoin(path_dir, "/");
	if (!dir_path)
		return (NULL);
	full_path = ft_strjoin(dir_path, cmd);
	free(dir_path);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path); //cmd found and is executable
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char *cmd)
{
	int		i;
	char	*full_path;
	char	**path;

	path = get_envar_path(); //simple cmd without '/', to find the folder in PATH
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path = build_and_check_path(cmd, path[i]);
		if (full_path)
		{
			free_matrix(path);
			return (full_path);
		}
		i++;
	}
	free_matrix(path);
	return (NULL); //no path found
}

char	*set_path(char *cmd)
{
	if (ft_strchr(cmd, '/')) //could be absolute or relative
	{
		if (access(cmd, X_OK) == 0)
			return (cmd); //is executable
		return (NULL); //exists but is not executable
	}
	return (search_in_paths(cmd));
}

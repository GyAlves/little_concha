#include "../minishell.h"

char	**get_path(void)
{
	char 	*path;
	char	**envar_path;

	path = getenv("PATH");
	if (path == NULL)
	{
		envar_path = ft_calloc(3, sizeof(char *));
		envar_path[0] = ft_strdup("/bin");
		envar_path[1] = ft_strdup("/usr/bin");
		envar_path[2] = NULL;
	}
	else
		envar_path = ft_split(path, ':');
	return (envar_path);
}

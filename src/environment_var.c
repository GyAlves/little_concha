#include "../minishell.h"

char	**get_path(void)//, char **envp)
{
	char 	**envar_path;
	
	envar_path = getenv("PATH");
	if (envar_path == NULL)
		return ("/bin:/usr/bin");
	ft_split(envar_path, ':');
	return (envar_path);
}
#include "../minishell.h"

char	**get_path(void)
{
	char 	*path;
	char	**envar_path;

	path = getenv("PATH");
	if (path == NULL)
	{
		path = "/bin:/usr/bin";
		ft_calloc(1, sizeof(char *)); //não entendi
	}
	else
		envar_path = ft_split(path, ':');
	return (envar_path);
}
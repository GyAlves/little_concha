#include "../minishell.h"

int	envar_handler(int c, char **v, char **envp)
{
	int		i;
	char 	*envar;

	i = 0;
	/*envar = envp[i];
	while (envar != NULL)
	{
		printf("%s\n", envar);
		i++;
		envar = envp[i];
	}*/
	envar = getenv("PATH");
	if (envar == NULL)
	{
		printf("command not found: %s\n", v[1]);
		return (1);
	}
	printf("env variables: %s\n", envar);

	return (0);
}
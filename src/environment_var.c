#include "../minishell.h"

int	envar_handler(int c, char **v, t_command cmd)//, char **envp)
{
	//int		i;
	//char 	*envar;

	//i = 0;
	/*envar = envp[i];
	while (envar != NULL)
	{
		printf("%s\n", envar);
		i++;
		envar = envp[i];
	}
	envar = getenv("PATH");
	if (envar == NULL)
	{
		printf("command not found: %s\n", v[1]);
		return (1);
	}
	printf("env variables: %s\n", envar);*/
	(char **)cmd = getenv("PATH");
	if (&cmd == NULL)
		(char **)cmd = "/bin:/usr/bin";
	ft_split(&cmd, ':');
	return (0);
}
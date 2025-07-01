#include "../../minishell.h"

int	count_init_envar(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**alloc_init_envar_arr(int count)
{
	char	**new_envp;

	new_envp = ft_calloc(count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

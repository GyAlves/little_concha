#include "../../minishell.h"

int	count_first_envar(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**alloc_first_envar_arr(int count)
{
	char	**new_envp;
	
	new_envp = ft_calloc(count + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

int	cp_first_envar_entries(char **new_envp, char **old_envp, int count)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < count)
	{
		temp = ft_strdup(old_envp[i]);
		if (!temp)
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (0);
		}
		new_envp[i] = temp;
		i++;
	}
	return (1);
}

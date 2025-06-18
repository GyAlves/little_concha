#include "../../minishell.h"

char	*find_env_var(char **envp, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 && envp[i][len] == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	update_env_var(t_minishell *sh, char* key, char *val)
{
	int		i;
	int		count;
	char	*temp;
	char	*env_entry;
	char	**new_envp;

	env_entry = ft_strjoin(key, "=");
	if (!env_entry)
		return ;
	temp = ft_strjoin(env_entry, val);
	free(env_entry);
	if (!temp)
		return ;
	env_entry = temp;
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, ft_strlen(key)) == 0 && sh->envp[i][ft_strlen(key)] == '=')
		{
			sh->envp[i] = env_entry;
			return ;
		}
		i++;
	}
	count = i;
	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
	{
		free (env_entry);
		return ;
	}
	i = 0;
	while ( i < count)
	{
		new_envp[i] = ft_strdup(sh->envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			free(env_entry);
			return ;
		}
		i++;
	}
	new_envp[count] = env_entry;
	new_envp[count + 1] = NULL;
	free_matrix(sh->envp);
	sh->envp = new_envp;
}
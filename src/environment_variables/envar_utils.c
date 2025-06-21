#include "../../minishell.h"

char	*find_envar(char **envp, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 \
		&& envp[i][len] == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*create_envar_entry(char *key, char *val) //can be used in export built-in
{
	char	*temp;
	char	*envar_entry;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	envar_entry = ft_strjoin(temp, val);
	free(temp);
	if (!envar_entry)
		return (NULL);
	return (envar_entry);
}

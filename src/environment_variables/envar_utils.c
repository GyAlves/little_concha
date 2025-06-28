#include "../../minishell.h"

static int	is_valid_key(const char *key)
{
	int	i;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_id(char *envar)
{
	int		valid;
	char	*equal;
	char	*key;

	if (!envar)
		return (0);
	equal = ft_strchr(envar, '=');
	if (equal)
		key = ft_strndup(envar, equal - envar);
	else
		key = ft_strdup(envar);
	if (!key)
		return (0);
	valid = is_valid_key(key);
	free(key);
	return (valid);
}

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

int	cpy_envar_entries(char **new_envp, char **old_envp, int count)
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

char	*create_envar_entry(char *key, char *val)
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

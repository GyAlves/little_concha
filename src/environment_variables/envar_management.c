#include "../../minishell.h"

static char	**alloc_envar_array(int count)
{
	char	**new_envp;

	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

static char	**append_envar(t_minishell *sh, char *envar_entry, int count)
{
	char	**new_envp;

	new_envp = alloc_envar_array(count);
	if (!new_envp)
		return (NULL);
	if (!cpy_envar_entries(new_envp, sh->envp, count))
	{
		free(new_envp);
		return (NULL);
	}
	new_envp[count] = ft_strdup(envar_entry);
	if (!new_envp[count])
	{
		free_matrix(new_envp);
		return (NULL);
	}
	new_envp[count + 1] = NULL;
	return (new_envp);
}

static int	update_curr_envar(t_minishell *sh, char *envar_entry, char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, ft_strlen(key)) == 0 \
		&& (sh->envp[i][ft_strlen(key)] == '=' \
		|| sh->envp[i][ft_strlen(key)] == '\0'))
		{
			tmp = sh->envp[i];
			sh->envp[i] = ft_strdup(envar_entry);
			free(tmp);
			if (!sh->envp[i])
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	update_envar(t_minishell *sh, char *key, char *val)
{
	int		count;
	char	*envar_entry;
	char	**new_envp;

	if (!key)
		return ;
	if (val)
		envar_entry = create_envar_entry(key, val);
	else
		envar_entry = ft_strdup(key);
	if (!envar_entry)
		return ;
	if (update_curr_envar(sh, envar_entry, key))
	{
		free(envar_entry);
		return ;
	}
	count = count_init_envar(sh->envp);
	new_envp = append_envar(sh, envar_entry, count);
	free(envar_entry);
	if (!new_envp)
		return ;
	free_matrix(sh->envp);
	sh->envp = new_envp;
}

void	free_minishell(t_minishell *sh)
{
	int	i;
	if (!sh->envp)
		return ;
	i = 0;
	while (sh->envp[i])
	{
		free(sh->envp[i]);
		i++;
	}
	free(sh->envp);
	sh->envp = NULL;
	clear_history();
}
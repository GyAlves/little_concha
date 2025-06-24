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

static void	sort_envp(char **envp, int count)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		i = 0;
		swapped = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_sorted_envar(t_minishell *sh)
{
	int		count;
	char	**copy;

	count = ft_arrlen(sh->envp);
	copy = alloc_first_envar_arr(count);
	if (!copy)
		return ;
	if (!cp_first_envar_entries(copy, sh->envp, count))
		return ;
	sort_envp(copy, count);
	
	int i = 0;
	while (copy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(copy[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	free_matrix(copy);
}

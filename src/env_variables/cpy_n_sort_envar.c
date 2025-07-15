#include "minishell.h"

static void	sort_envar(char **envp, int count)
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

char	**cpy_and_sort_envar(t_minishell *sh)
{
	int		count;
	char	**copy;

	count = count_init_envar(sh->envp);
	copy = alloc_init_envar_arr(count);
	if (!copy)
		return (NULL);
	if (!copy_env_variables(copy, sh->envp, count))
	{
		free_matrix(copy);
		return (NULL);
	}
	sort_envar(copy, count);
	return (copy);
}

void	print_envar(char **envp)
{
	int		i;
	char	*equal;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		ft_putstr_fd("declare -x ", 1);
		if (equal)
		{
			write(1, envp[i], equal - envp[i]);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equal + 1, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd(envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}

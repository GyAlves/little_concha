#include "../../minishell.h"

static void	print_export_err(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	print_sorted_envar(t_minishell *sh)
{
	char	**copy;

	copy = cpy_and_sort_envar(sh);
	if (!copy)
		return ;
	print_envar(copy);
	free_matrix(copy);
}

static void	set_envar(t_minishell *sh, char *arg)
{
	char	*key;
	char	*equal;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!is_valid_id(arg))
	{
		print_export_err(arg);
		sh->exit_status = 1;
		return ;
	}
	if (equal)
	{
		key = ft_strndup(arg, equal - arg);
		value = equal + 1;
		if (key)
			update_envar(sh, key, value);
		free(key);
	}
	else
		update_envar(sh, arg, "");
}

void	bi_export(t_minishell *sh, t_command *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		print_sorted_envar(sh);
		sh->exit_status = 0;
		return ;
	}
	while (cmd->args[i])
	{
		set_envar(sh, cmd->args[i]);
		i++;
	}
	if (!sh->exit_status)
		sh->exit_status = 0;
}

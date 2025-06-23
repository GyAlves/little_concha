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

static int	is_valid_id(char *envar)
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

static void	print_export_err(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	export_var(t_minishell *sh, char *arg)
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
		i = 0;
		while (sh->envp[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sh->envp[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		sh->exit_status = 0;
		return ;
	}
	while (cmd->args[i])
	{
		export_var(sh, cmd->args[i]);
		i++;
	}
	if (!sh->exit_status)
		sh->exit_status = 0;
}

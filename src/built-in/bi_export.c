#include "../../minishell.h"
//export: lista as variaveis de forma ordenada
//export VAR: cria uma variável vazia
//export vAR=66: cria uma variável e atribui uma valor a mesma
/*export 66=VAR: imprime a menssagem de erro: "export: not an identifier: 66"
ps.: se a envar existir o valor não é atribuido, porém não retorna nenhum tipo de erro*/
//export A=1 B=2: cria multiplas envars

static int	is_valid_id(char *envar)
{
	int	i;

	i = 0;
	if (!envar || !(ft_isalpha(envar[0] || envar[0] == '_')))
		return (0);
	while (envar[i])
	{
		if (!(ft_isalnum(envar[i]) || envar[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_err(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
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
}

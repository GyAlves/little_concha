#include "../../minishell.h"

char	*expand_varriable(t_minishell *sh, char *str)
{
	char	*key;
	char	*val;
	char	*res;

	if (str[0] != '$')
	{
		res = ft_strdup(str);
		return (res);
	}
	key = str + 1;
	val = find_envar(sh->envp, key);
	if (val)
		res = ft_strdup(val);
	else
		res = ft_strdup("");
	if (!res)
		return (NULL);
	return (res);
}

char	*replace_variables(t_minishell *sh, char *input)
{
	char	*res;
	res = expand_varriable(sh, input);
	return (res);
}

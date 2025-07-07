#include "../../minishell.h"

static int	count_cmd_args(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	**cpy_cmd_args(char **args, char **n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
			i += 2;
		else
		{
			n_args[j] = ft_strdup(args[i]);
			if (!n_args[j])
			{
				free_matrix(n_args);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	return (n_args);
}

char	**filter_n_rm_redir(char **args, int *n_count)
{
	char	**n_args;

	*n_count = count_cmd_args(args);
	n_args = ft_calloc(*n_count + 1, sizeof(char *));
	if (!n_args)
		return (NULL);
	n_args = cpy_cmd_args(args, n_args);
	return (n_args);
}

t_redir_type	get_redir_type(char *str)
{
	if (!str)
		return (INVALID);
	if (!ft_strcmp(str, ">"))
		return (R_OUT);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<"))
		return (R_IN);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	return (INVALID);
}

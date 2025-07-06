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

int	count_redirs(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}

int	fill_redirs(t_command *cmd, char **args)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (get_redir_type(args[i]) != INVALID)
		{
			if (!args[i + 1])
				return (0);
			cmd->redirects[count].type = get_redir_type(args[i]);
			if (cmd->redirects[count].type == INVALID)
				return (0);
			cmd->redirects[count].filename = ft_strdup(args[i + 1]);
			if (!cmd->redirects[count].filename)
				return (0);
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (1);
}

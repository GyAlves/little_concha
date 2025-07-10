#include "../../minishell.h"

int	count_cmd_args(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_pipe(args[i]))
			break ;
		else if (is_redir(args[i]))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**cpy_cmd_args(char **args, char **n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redir(args[i]))
			i += 2;
		else if (is_pipe(args[i]))
			i++;
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
	n_args[j] = NULL;
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

int	init_cmd_arr(t_command **cmd, int cmd_count)
{
	*cmd = ft_calloc(cmd_count, sizeof(t_command));
	if (!*cmd)
		return (0);
	return (1);
}

int	fill_cmd(char **args, t_command *cmd)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (args[i])
	{
		if (is_pipe(args[i]) || !args[i + 1])
		{
			if (!args[i + 1] && !is_pipe(args[i]))
				i++;
			if (!parse_single_cmd(&cmd[j], args, start))
			{
				while (j-- > 0)
					free_cmd_struct(&cmd[j]);
				return (0);
			}
			start = i + 1;
			j++;
		}
		i++;
	}
	return (1);
}

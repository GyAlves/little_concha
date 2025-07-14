#include "../../minishell.h"

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
		if (is_pipe(args[i]) || args[i + 1] == NULL)
		{
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

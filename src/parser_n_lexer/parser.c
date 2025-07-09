#include "../../minishell.h"

static int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

static int	init_cmd_redit(t_command *cmd, char **args)
{
	cmd->redir_count = count_redirs(args);
	cmd->redirects = ft_calloc(cmd->redir_count + 1, sizeof(t_redirect));
	if (!cmd->redirects)
		return (0);
	if (!fill_redirs(cmd, args))
	{
		free(cmd->redirects);
		return (0);
	}
	return (1);
}

static int	parse_single_cmd(t_command *cmd, char **args, int start, int end)
{
	char	**cmd_args;
	int		n_count;

	cmd->piped = 0;
	cmd->redirects = NULL;
	cmd->redir_count = 0;
	cmd_args = cpy_cmd_args(args + start, NULL);
	if (!cmd_args)
		return (0);
	if (!init_cmd_redit(cmd, args + start))
	{
		free_matrix(cmd_args);
		return (0);
	}
	cmd_args = filter_n_rm_redir(cmd_args, &n_count);
	if (!cmd_args)
	{
		free(cmd->redirects);
		return (0);
	}
	cmd->args = cmd_args;
	return (1);
}

int	parse_n_init_cmd(t_minishell *sh, t_command **cmd, char **args)
{
	int	i;
	int	j;
	int	cmd_count;
	int	start;

	if (!args || !args[0])
		return (0);
	cmd_count = count_pipes(args);
	*cmd = ft_calloc(cmd_count, sizeof(t_command));
	if (!*cmd)
		return (0);
	if (cmd_count == 1)
		return (parse_single_cmd(*cmd, args, 0, 0));
	(*cmd)->piped = 1;
	i = 0;
	j = 0;
	start = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0 || !args[i + 1])
		{
			if (!parse_single_cmd(&(*cmd)[j], args, start, i))
			{
				while (j-- > 0)
					free_cmd_struct(&(*cmd)[j]);
				free(*cmd);
				return (0);
			}
			start = i + 1;
			j++;
		}
		i++;
	}
	free_matrix(args);
	return (1);
}

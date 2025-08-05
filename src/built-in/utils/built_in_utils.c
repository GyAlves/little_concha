/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:30:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:30:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}

int	is_parent_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}

void	print_cd_no_file_nor_dir(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

bool	is_key_match(const char *s, const char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(s, key, key_len) == 0)
	{
		if (s[key_len] == '=' || s[key_len] == '\0')
			return (true);
	}
	return (false);
}

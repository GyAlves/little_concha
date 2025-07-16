/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cd_no_file_nor_dir(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static char	*cd_envar_home(t_minishell *sh)
{
	char	*target;

	target = find_envar(sh->envp, "HOME");
	if (!target)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	target += 5;
	if (!target[0])
	{
		ft_putstr_fd("cd: HOME is empty\n", 2);
		return (NULL);
	}
	return (target);
}

static int	change_curr_dir(t_minishell *sh, char *target)
{
	char	*cwd;

	if (chdir(target) == -1)
	{
		print_cd_no_file_nor_dir(target);
		return (0);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	update_envar(sh, "PWD", cwd);
	free(cwd);
	return (1);
}

void	bi_cd(t_minishell *sh, t_command *cmd)
{
	char	*target;

	if (!cmd->args[1])
	{
		target = cd_envar_home(sh);
		if (!target)
		{
			sh->exit_status = 1;
			return ;
		}
	}
	else
		target = cmd->args[1];
	if (!change_curr_dir(sh, target))
	{
		sh->exit_status = 1;
		return ;
	}
	sh->exit_status = 0;
}

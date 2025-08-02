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
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		print_cd_no_file_nor_dir(target);
		if (old_pwd)
			free(old_pwd);
		return (0);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (old_pwd)
			free(old_pwd);
		return (0);
	}
	if (old_pwd)
		update_envar(sh, "OLDPWD", old_pwd);
	update_envar(sh, "PWD", cwd);
	free(cwd);
	if (old_pwd)
		free(old_pwd);
	return (1);
}

static char	*cd_envar_oldpwd(t_minishell *sh)
{
	char	*target;

	target = find_envar(sh->envp, "OLDPWD");
	if (!target)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	target += 7;
	if (!target[0])
	{
		ft_putstr_fd("cd: OLDPWD is empty\n", 2);
		return (NULL);
	}
	return (target);
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
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		char	*oldpwd_target;
		
		target = cd_envar_oldpwd(sh);
		if (!target)
		{
			sh->exit_status = 1;
			return ;
		}
		oldpwd_target = ft_strdup(target);
		if (!oldpwd_target)
		{
			sh->exit_status = 1;
			return ;
		}
		if (!change_curr_dir(sh, target))
		{
			free(oldpwd_target);
			sh->exit_status = 1;
			return ;
		}
		write(1, oldpwd_target, ft_strlen(oldpwd_target));
		write(1, "\n", 1);
		free(oldpwd_target);
		sh->exit_status = 0;
		return ;
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

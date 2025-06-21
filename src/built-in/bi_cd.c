#include "../../minishell.h"

static void	print_cd_no_file_nor_dir(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
		write(2, path, ft_strlen(path));
	ft_putstr_fd(": No such file or directory\n", 2);
}

static char	*cd_envar_home(t_minishell *sh)
{
	char *target;

	target = find_envar(sh->envp, "HOME"); //uses HOME
	if (!target)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	target += 5; //advances to after "HOME=" taking only the value
	if (!target[0]) //if it's empty, returns error
	{
		ft_putstr_fd("cd: HOME is empty\n", 2);
		return (NULL);
	}
	return (target);
}

void	bi_cd(t_minishell *sh, t_command *cmd)
{
	char	*cwd; //stores the curr dir
	char	*target; //target dir

	if (!cmd->args[1]) //just cd to go to HOME
	{
		target = cd_envar_home(sh);
		if (!target)
		{
			sh->exit_status = 1;
			return ;
		}
	}
	else
		target = cmd->args[1]; //dir to go
	if (chdir(target) == -1) //tryes to change to target dir
	{
		print_cd_no_file_nor_dir(target);
		sh->exit_status = 1;
		return  ;
	}
	cwd = getcwd(NULL, 0); //get the absolute path
	if (!cwd)
	{
		sh->exit_status = 1;
		return ;
	}
	update_envar(sh, "PWD", cwd); //update PWD
	free(cwd);
	sh->exit_status = 0;
}

/*

void	bi_cd(t_minishell *sh, t_command *cmd)
{
	char	*cwd;
	char	*target;
	char	*oldpwd;
//can be a function
	oldpwd = getcwd(NULL, 0); //saves current dir
	if (!oldpwd)
	{
		sh->exit_status = 1;
		return ;
	}
//can be a function
	if (!cmd->args[1]) //just cd to go to HOME
	{
		target = find_envar(sh->envp, "HOME"); //uses HOME
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
		target += 5; //advances to after "HOME=" taking only the value
		if (!target[0]) //if it's empty, returns error
		{
			ft_putstr_fd("cd: HOME is empty\n", 2);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
	}
//can be a function or can be removed
	else if (ft_strncmp(cmd->args[1], "-",  2) == 0) //cd - returns to the latest dir
	{
		target = find_envar(sh->envp, "OLDPWD"); //uses OLDPWD
		if (!target)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
		target += 7;
		if (!target[0])
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
	}
	else
	{
		if (!cmd->args[1])
		{
			print_cd_no_file_nor_dir(NULL);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
		target = cmd->args[1]; //uses provided arg
	}
	if (chdir(target) == -1) //tryes to change dir
	{
		print_cd_no_file_nor_dir(target);
		free (oldpwd);
		sh->exit_status = 1;
		return  ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(oldpwd);
		sh->exit_status = 1;
		return ;
	}
	if (oldpwd)
		update_envar(sh, "OLDPWD", oldpwd); //update OLDPWD
	if (cwd)
		update_envar(sh, "PWD", cwd); //update PWD
	free(oldpwd);
	free(cwd);
	sh->exit_status = 0;
}

*/
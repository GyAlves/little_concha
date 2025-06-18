#include "../../minishell.h"

static void	print_cd_no_file_nor_dir(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
		write(2, path, ft_strlen(path));
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	bi_cd(t_minishell *sh, t_command *cmd)
{
	char	*cwd;
	char	*target;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0); //saves current dir
	if (!oldpwd)
	{
		sh->exit_status = 1;
		return ;
	}
	if (!cmd->args[1]) //just cd
	{
		target = find_env_var(sh->envp, "HOME"); //uses HOME
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
		target += 5;
		if (!target[0])
		{
			ft_putstr_fd("cd: HOME is empty\n", 2);
			free(oldpwd);
			sh->exit_status = 1;
			return ;
		}
	}
	else if (ft_strncmp(cmd->args[1], "-",  2) == 0) //cd -
	{
		target = find_env_var(sh->envp, "OLDPWD"); //uses OLDPWD
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
		update_env_var(sh, "OLDPWD", oldpwd); //update OLDPWD
	if (cwd)
		update_env_var(sh, "PWD", cwd); //update PWD
	free(oldpwd);
	free(cwd);
	sh->exit_status = 0;
}

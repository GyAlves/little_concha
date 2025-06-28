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
	char	*target;

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

static int	change_curr_dir(t_minishell *sh, char *target)
{
	char	*cwd; //stores the curr dir

	if (chdir(target) == -1) //tryes to change to target dir
	{
		print_cd_no_file_nor_dir(target);
		return (0);
	}
	cwd = getcwd(NULL, 0); //get the absolute path
	if (!cwd)
		return (0);
	update_envar(sh, "PWD", cwd); //update PWD
	free(cwd);
	return (1);
}

void	bi_cd(t_minishell *sh, t_command *cmd)
{
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
	if (!change_curr_dir(sh, target))
	{
		sh->exit_status = 1;
		return ;
	}
	sh->exit_status = 0;
}

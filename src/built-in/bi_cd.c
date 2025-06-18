#include "../../minishell.h"

static void	print_cd_no_file_nor_dir(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
		write(2, path, ft_strlen(path));
	ft_putstr_fd(": No such file or directory\n", 2);
}

char	*find_env_var(char **envp, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 && envp[i][len] == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	update_env_var(t_minishell *sh, char* key, char *val)
{
	int		i;
	int		count;
	char	*temp;
	char	*env_entry;
	char	**new_envp;

	env_entry = ft_strjoin(key, "=");
	if (!env_entry)
		return ;
	temp = ft_strjoin(env_entry, val);
	free(env_entry);
	if (!temp)
		return ;
	env_entry = temp;
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, ft_strlen(key)) == 0 && sh->envp[i][ft_strlen(key)] == '=')
		{
			sh->envp[i] = env_entry;
			return ;
		}
		i++;
	}
	count = i;
	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
	{
		free (env_entry);
		return ;
	}
	i = 0;
	while ( i < count)
	{
		new_envp[i] = ft_strdup(sh->envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			free(env_entry);
			return ;
		}
		i++;
	}
	new_envp[count] = env_entry;
	new_envp[count + 1] = NULL;
	free_matrix(sh->envp);
	sh->envp = new_envp;
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

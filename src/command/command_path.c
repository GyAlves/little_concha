/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:38:11 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/06 17:38:14 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_envar_path(char **envp)
{
	char	*path;
	char	**envar_path;

	path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp;
			break ;
		}
		envp++;
	}
	if (path == NULL)
		return (NULL);
	envar_path = ft_split(path, ':');
	if (!envar_path)
		return (NULL);
	return (envar_path);
}

static char	*build_and_check_path(char *cmd, char *path_dir)
{
	char	*dir_path;
	char	*full_path;

	dir_path = ft_strjoin(path_dir, "/");
	if (!dir_path)
		return (NULL);
	full_path = ft_strjoin(dir_path, cmd);
	free(dir_path);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **envp)
{
	int		i;
	char	*full_path;
	char	**path;

	path = get_envar_path(envp);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path = build_and_check_path(cmd, path[i]);
		if (full_path)
		{
			free_string_matrix(path);
			return (full_path);
		}
		i++;
	}
	free_string_matrix(path);
	return (NULL);
}

char	*set_path(char *cmd, char **envp)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	return (search_in_paths(cmd, envp));
}

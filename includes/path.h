/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:43:39 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 19:45:07 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

/* Libs */
static char	**default_path(void);
char	    **get_envar_path(void);
static char	*build_and_check_path(char *cmd, char *path_dir);
static char	*search_in_paths(char *cmd);
char	    *set_path(char *cmd);
#endif
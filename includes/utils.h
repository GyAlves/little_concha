/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:55:08 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/07/11 20:15:56 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Libs */
char	**read_input(char **prompt);
void    print_cmd_err(char *cmd);
static void	print_cd_no_file_nor_dir(char *path);
char	*replace_variables(t_minishell *sh, char *input);
static void	print_num_arg_required(t_command *cmd);
static void	print_export_err(char *arg);
int	is_valid_id(char *envar);
static void	print_unset_err(char *arg);

#endif
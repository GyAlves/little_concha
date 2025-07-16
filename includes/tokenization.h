/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:02:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 09:27:33 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

/* Forward declarations */
typedef struct s_command    t_command;
typedef enum e_redir_type   t_redir_type;

/* LEXER Functions */
char    **lexer(char *input);
t_redir_type	get_redir_type(char *str);
int				is_pipe(char *str);

/* PARSER Functions */
char			**filter_n_rm_redir(char **args, int *n_count);
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(char **args, t_command *cmd);
int				count_pipes(char **args);

#endif
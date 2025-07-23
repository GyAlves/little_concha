/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:02:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/22 19:59:47 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

/* Forward declarations */
typedef struct s_command	t_command;
typedef enum e_redir_type	t_redir_type;

#include "minshell.h"

/* Structs */
typedef struct s_token
{
    char *content;
    bool was_double;
    bool was_single;
} token_t;

/* LEXER DOMAIN - Token creation and input processing */
token_t			*lexer(char *input);
t_redir_type	get_redir_type(char *str);
int				is_pipe(char *str);

/* PARSER DOMAIN - Command structure parsing and analysis */
char			**filter_n_rm_redir(token_t *args, int *n_count);
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(token_t *args, t_command *cmd);
int				count_pipes(token_t *args);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:02:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 18:26:37 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

/* Forward declarations */
typedef struct s_command	t_command;
typedef enum e_redir_type	t_redir_type;

/* LEXER DOMAIN - Token creation and input processing */
// src/tokenization/lexer/lexer.c
char			**lexer(char *input);
// src/tokenization/lexer/utils/lexer_validation_utils.c
t_redir_type	get_redir_type(char *str);
int				is_pipe(char *str);

/* PARSER DOMAIN - Command structure parsing and analysis */
// src/tokenization/parser/utils/parser_filter_utils.c
char			**filter_n_rm_redir(char **args, int *n_count);
// src/tokenization/parser/utils/parser_command_utils.c
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(char **args, t_command *cmd);
// src/tokenization/parser/utils/parser_count_utils.c
int				count_pipes(char **args);

#endif
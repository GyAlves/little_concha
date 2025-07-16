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
typedef struct s_command    t_command;
typedef enum e_redir_type   t_redir_type;

/* Tokenization and parsing functions */
// src/tokenization/lexer/lexer.c
char    **lexer(char *input);
// src/tokenization/parser/utils/parser_pipes_utils.c
int	is_pipe(char *str);
int	count_pipes(char **args);
// src/parser_n_lexer/parser_utils.c
char			**filter_n_rm_redir(char **args, int *n_count);
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(char **args, t_command *cmd);
// src/parser_n_lexer/token_utils.c
t_redir_type	get_redir_type(char *str);
int				is_redir(char *str);

#endif
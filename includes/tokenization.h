/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:02:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/23 21:19:28 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

/* Forward declarations */
typedef struct s_command	t_command;
typedef enum e_redir_type	t_redir_type;
typedef struct s_minishell	t_minishell;

/* LEXER DOMAIN - Token creation and input processing */
t_token			*lexer(char *input, t_minishell *shell);
t_token			fill_token(char *input, int *pos);
int				count_tokens(char *input);
t_redir_type	get_redir_type(char *str);
int				is_pipe(char *str);

/* PARSER DOMAIN - Command structure parsing and analysis */
char			**filter_n_rm_redir(t_token *args, int *n_count);
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(t_token *args, t_command *cmd);
int				count_pipes(t_token *args);
char            **tokens_parser(t_token *tokens, t_minishell *shell);
void			expand_tokens(t_minishell *shell, t_token *tokens);

/* TOKEN PROCESSING FUNCTIONS */
char			*non_quoted_token(char *content, t_minishell *shell);
char			*single_quoted_token(char *content);
char			*double_quoted_token(char *content, t_minishell *shell);
char			*expanded_variable(char *content, t_minishell *shell);
bool			is_variable_expansion(char *content);

#endif
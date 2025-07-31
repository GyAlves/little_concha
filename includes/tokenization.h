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

/* STRUCTS */
typedef struct s_token
{
	char	*content;
	bool	was_double;
	bool	was_single;
	bool	has_operator;
}			t_token;

typedef struct s_token_temp
{
	int		start_temp;
	bool	in_single_temp;
	bool	in_double_temp;
	bool	was_single_temp;
	bool	was_double_temp;
	char	*content_temp;
}				t_token_temp;

// src/tokenization/lexer/utils/lexer_count_tokens.c
int				count_tokens(char *input);
// src/tokenization/lexer/utils/lexer_fill_token.c
t_token			fill_token(char *input, int *pos);
// src/tokenization/lexer/utils/lexer_validation_utils.c
t_redir_type	get_redir_type(char *str);
int				is_pipe(char *str);
int				is_operator(char c);
int				is_str_operator(char *str);
// src/tokenization/lexer/lexer.c
t_token			*lexer(char *input, t_minishell *shell);
// src/tokenization/parser/utils/parser_command_utils.c
int				init_cmd_arr(t_command **cmd, int cmd_count);
int				fill_cmd(t_token *args, t_command *cmd);
// src/tokenization/parser/utils/parser_count_utils.c
int				count_pipes(t_token *args);
// src/tokenization/parser/utils/parser_expansion_utils.c
char			*expand_envar(t_minishell *shell, char *key);
char			*join_and_free(char *result, char *to_add);
// src/tokenization/parser/utils/parser_quotes_utils.c
char			*process_quoted_segment(const char *content, int *i, \
				int start, t_minishell *shell);
char			*process_unquoted_segment(const char *content, int *i, \
				int start, t_minishell *shell);
char			*strip_outer_quotes(char *content, int len, t_minishell *shell);
char			*expand_and_free(char *content_to_expand, t_minishell *shell);
char			*process_mixed_quotes(char *content, t_minishell *shell);
// src/tokenization/parser/utils/parser_quotes.c
char			*non_quoted_token(char *content, t_minishell *shell);
char			*single_quoted_token(char *content);
char			*double_quoted_token(char *content, t_minishell *shell);
bool			is_variable_expansion(char *content);
// src/tokenization/parser/parser_variable_expansion.c
char			*expanded_variable(char *content, t_minishell *shell);
// src/tokenization/parser/parser.c
bool			expand_tokens(t_minishell *shell, t_token *tokens);
#endif
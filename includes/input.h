/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/23 21:00:13 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/* Forward declarations */
typedef struct s_minishell	t_minishell;

/* Input functions */
bool	read_and_validate_prompt(char **prompt, t_minishell *shell);
bool	read_input(t_minishell *shell, char **prompt_line, t_token **tokens);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:45:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/* Forward declarations */
typedef struct s_minishell	t_minishell;

/* Input functions */
// src/input/utils/input_utils.c
char	**read_input(t_minishell *shell, char **prompt);
// src/input/utils/prompt_setup_utils.c
bool	setup_prompt(t_minishell *shell, char **prompt, char ***args);

#endif
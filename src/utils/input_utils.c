/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:57:42 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/06/21 18:03:40 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input(char **prompt)
{
	char	**args;

	*prompt = readline(PROMPT);
	if (!*prompt)
		return (NULL);
	add_history(*prompt);
	args = ft_split(*prompt, ' ');
	return (args);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:01:03 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/14 18:01:40 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lexer(char *input) //divide as str input em um arr chamdo token, e separa por espaço
{
	char	**tokens; //ex: input = "echo hello, world | cat", vira tokens = {"echo", "hello,", "world", "|", "cat", NULL}.
	if (!input || !*input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}

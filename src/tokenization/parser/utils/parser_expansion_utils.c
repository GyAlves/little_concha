/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:09 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/31 15:36:11 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

char	*join_and_free(char *result, char *to_add)
{
	char	*temp;

	temp = ft_strjoin(result, to_add);
	free(result);
	free(to_add);
	return (temp);
}

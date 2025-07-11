/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:35:30 by galves-a          #+#    #+#             */
/*   Updated: 2025/07/11 20:36:02 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_args(char *arg)
{
	if (!arg)
		return (false);
	if (!((*arg == '+' || *arg == '-') || (*arg >= '0' && *arg <= '9')))
		return (false);
	if ((*arg == '+' || *arg == '-') && (!(arg[1] >= '0' && arg[1] <= '9')))
		return (false);
	while (*++arg)
	{
		if (!(*arg >= '0' && *arg <= '9'))
			return (false);
	}
	return (true);
}
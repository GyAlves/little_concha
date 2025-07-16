/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:16:03 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/07 13:16:08 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
=======
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:16:03 by fleite-j          #+#    #+#             */
/*   Updated: 2025/07/18 19:29:24 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "libft.h"
=======
#include "../libft.h"
>>>>>>> e808775af988923e17434033f446e2d9f779cd2e

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

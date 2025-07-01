#include "../../minishell.h"

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

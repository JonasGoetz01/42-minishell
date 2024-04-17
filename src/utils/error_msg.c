#include "../../inc/minishell.h"

void	ft_print_error(const char *msg, const char *arg)
{
	if (arg)
		printf("minishell: %s: %s\n", arg, msg);
	else
		printf("minishell: %s\n", msg);
}

#ifndef HELPERS_H
# define HELPERS_H

# include "../../inc/minishell.h"
# include <stdarg.h>

t_token	**create_token_list(int count, ...);

void	free_token_list(t_token **head);

#endif
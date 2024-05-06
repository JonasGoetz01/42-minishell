#include "../../inc/minishell.h"

t_token	*ft_first_valid_token(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			if (token->value && token->value[0] == '\0')
			{
				if (token->next)
				{
					if (token->next->type == TOKEN_DOUBLE_QUOTE
						|| token->next->type == TOKEN_SINGLE_QUOTE)
						break ;
				}
			}
			else
				break ;
		}
		token = token->next;
	}
	return (token);
}

#include "../../inc/minishell.h"

void	ft_org_tokens(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			token->type = TOKEN_CMD;
			token = token->next;
			while (token && token->type == TOKEN_WORD)
			{
				token->type = TOKEN_ARG;
				token = token->next;
			}
		}
		else
			token = token->next;
	}
}

#include "../../inc/minishell.h"

void	ft_org_tokens(t_ast_node *ast)
{
	t_token	*token;

	if (!ast)
		return ;
	token = ast->token;
	if (!token)
		return ;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			break ;
		token = token->next;
	}
	if (token)
	{
		if (token->type == TOKEN_WORD)
		{
			token->type = TOKEN_CMD;
			token = token->next;
			while (token)
			{
				if (token->type == TOKEN_WORD)
					token->type = TOKEN_ARG;
				token = token->next;
			}
		}
		else if (token->type == TOKEN_LESS || token->type == TOKEN_GREATER
			|| token->type == TOKEN_DOUBLE_GREATER
			|| token->type == TOKEN_DOUBLE_LESS)
			ast->right->token->type = TOKEN_ARG;
	}
	ft_org_tokens(ast->left);
	ft_org_tokens(ast->right);
}

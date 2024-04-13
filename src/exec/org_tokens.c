#include "../../inc/minishell.h"

void	ft_org_tokens(t_ast_node *ast)
{
	t_token	*token;

	if (!ast)
		return ;
	token = ast->token;
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
	ft_org_tokens(ast->left);
	ft_org_tokens(ast->right);
}

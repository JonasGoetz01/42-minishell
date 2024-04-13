#include "../../inc/minishell.h"

void	ft_org_tokens(t_ast_node *ast)
{
	t_token	*token;

	if (!ast)
		return ;
	token = ast->token;
	if (!token)
		return ;
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
	ft_org_tokens(ast->left);
	ft_org_tokens(ast->right);
}

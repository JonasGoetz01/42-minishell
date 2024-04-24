#include "../../inc/minishell.h"

static void	ft_set_token_type_args(t_token **token)
{
	(*token)->type = TOKEN_CMD;
	(*token) = (*token)->next;
	while ((*token))
	{
		if ((*token)->type == TOKEN_WORD)
			(*token)->type = TOKEN_ARG;
		(*token) = (*token)->next;
	}
}

void	ft_org_tokens(t_ast_node *node)
{
	t_token	*token;

	if (!node)
		return ;
	token = node->token;
	if (!token)
		return ;
	if (token->type == TOKEN_WORD)
		ft_set_token_type_args(&token);
	else if (token->type == TOKEN_LESS || token->type == TOKEN_GREATER
		|| token->type == TOKEN_DOUBLE_GREATER
		|| token->type == TOKEN_DOUBLE_LESS)
	{
		if (node->right)
		{
			if (node->right->token)
				node->right->token->type = TOKEN_ARG;
		}
	}
	ft_org_tokens(node->left);
	ft_org_tokens(node->right);
}

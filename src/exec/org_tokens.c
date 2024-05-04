#include "../../inc/minishell.h"

static void	ft_combine_tokens(t_token *token1, t_token *token2)
{
	char	*new_value;

	if (token1 == NULL || token2 == NULL)
		return ;
	new_value = ft_strjoin(token1->value, token2->value);
	if (new_value == NULL)
		return ;
	free(token2->value);
	token2->value = new_value;
	token1->type = TOKEN_IGNORE;
}

static void	ft_combine_words(t_token *token)
{
	t_token	*next;

	while (token)
	{
		if (token->type == TOKEN_WORD || token->type == TOKEN_ARG)
		{
			next = token->next;
			while (next)
			{
				if (next->type == TOKEN_WORD || next->type == TOKEN_ARG)
				{
					ft_combine_tokens(token, next);
					break ;
				}
				else if (next->type == TOKEN_SPACE)
					break ;
				next = next->next;
			}
		}
		token = token->next;
	}
}

static void	ft_set_token_type_args(t_token *token)
{
	if (token == NULL)
		return ;
	token->type = TOKEN_CMD;
	token = token->next;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			token->type = TOKEN_ARG;
		token = token->next;
	}
}

static void	ft_set_token_type_redirs(t_ast_node *node, t_token *token)
{
	if (token->type == TOKEN_LESS || token->type == TOKEN_GREATER
		|| token->type == TOKEN_DOUBLE_GREATER
		|| token->type == TOKEN_DOUBLE_LESS)
	{
		if (node->right)
		{
			if (node->right->token)
			{
				token = node->right->token;
				while (token)
				{
					if (token->type == TOKEN_WORD)
						token->type = TOKEN_ARG;
					token = token->next;
				}
			}
		}
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
	ft_set_token_type_redirs(node, token);
	ft_combine_words(token);
	while (token)
	{
		if (token->type == TOKEN_WORD && token->value
			&& token->value[0] != '\0')
			break ;
		token = token->next;
	}
	ft_set_token_type_args(token);
	ft_org_tokens(node->left);
	ft_org_tokens(node->right);
}

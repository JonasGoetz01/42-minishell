#include "../../inc/minishell.h"

// Print the tokens
void	print_tokens(t_token *tokens)
{
	if (DEBUG)
	{
		printf("Tokens:\n");
		while (tokens != NULL)
		{
			printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
			tokens = tokens->next;
		}
	}
}

// Check if the token is an operator
int	isOperator(t_token token)
{
	return (token.type == TOKEN_AMPERSAND || token.type == TOKEN_BRACKET_L
		|| token.type == TOKEN_BRACKET_R || token.type == TOKEN_DOUBLE_AMPERSAND
		|| token.type == TOKEN_DOUBLE_GREATER || token.type == TOKEN_DOUBLE_LESS
		|| token.type == TOKEN_DOUBLE_PIPE || token.type == TOKEN_GREATER
		|| token.type == TOKEN_LESS || token.type == TOKEN_PIPE);
}

void	free_token(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	current = *tokens;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->value);
		free(temp);
		temp = NULL;
	}
	free(*tokens);
	*tokens = NULL;
}

void	prev_link_list(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

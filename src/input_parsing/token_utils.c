#include "../../inc/minishell.h"

size_t	token_count(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens != NULL)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token != NULL)
	{
		token->type = type;
		token->value = value;
		token->next = NULL;
	}
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens != NULL)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_token;
	}
}

// length of the token
// figures out the length of the token by checking for delimiters
int	token_length(const char *input, const char *delimiters)
{
	int	length;

	length = 0;
	while (input[length] != '\0' && !ft_strchr(delimiters, input[length]))
		length++;
	return (length);
}

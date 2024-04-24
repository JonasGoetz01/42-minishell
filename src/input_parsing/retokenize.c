#include "../../inc/minishell.h"

void	retokenize(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	char	*value;
	char	*token_value;
	t_token	*new_token;
	t_token	*temp;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if ((current->type == TOKEN_SINGLE_QUOTE
				|| current->type == TOKEN_DOUBLE_QUOTE) && current->next
			&& current->next->type == current->type)
		{
			new_token = create_token(TOKEN_WORD, "\0");
			temp = current->next;
			current->next = new_token;
			new_token->next = temp;
		}
		if (current->type == TOKEN_SINGLE_QUOTE
			|| current->type == TOKEN_DOUBLE_QUOTE)
		{
			temp = current;
			while (current->next && current->next->type != temp->type)
				current = current->next;
		}
		if (current->type == TOKEN_WORD && ft_strchr(current->value, ' '))
		{
			value = current->value;
			token_value = ft_strtok(value, " ");
			while (token_value != NULL)
			{
				new_token = create_token(TOKEN_WORD, ft_strdup(token_value));
				if (prev)
					prev->next = new_token;
				else
					*tokens = new_token;
				prev = new_token;
				token_value = ft_strtok(NULL, " ");
			}
			temp = current->next;
			current = temp;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

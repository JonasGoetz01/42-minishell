#include "../../inc/minishell.h"

void	remove_unused_spaces(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	current = *tokens;
	prev = NULL;
	temp = NULL;
	while (current)
	{
		if (current->type == TOKEN_DOUBLE_QUOTE
			|| current->type == TOKEN_SINGLE_QUOTE)
		{
			prev = current;
			current = current->next;
			while (current && current->type != prev->type)
			{
				temp = current;
				current = current->next;
			}
			prev = current;
			current = current->next;
		}
		else if (current->type == TOKEN_WORD && strcmp(current->value,
				" ") == 0)
		{
			temp = current;
			if (prev == NULL)
				*tokens = current->next;
			else
				prev->next = current->next;
			current = current->next;
			free(temp->value);
			free(temp);
		}
		else
		{
			prev = current;
			if (current)
				current = current->next;
		}
	}
}

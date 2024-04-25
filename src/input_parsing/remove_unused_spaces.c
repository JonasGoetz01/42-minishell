#include "../../inc/minishell.h"

void	remove_unused_spaces(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == TOKEN_SPACE)
		{
			if (!prev)
				*tokens = current->next;
			else
				prev->next = current->next;
			temp = current;
			current = current->next;
			free(temp->value);
			free(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

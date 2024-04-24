#include "../../inc/minishell.h"

void	combine_words_in_quotes(t_token **tokens)
{
	t_token			*current;
	int				num_tokens;
	t_token_type	type;
	t_token			*start;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_DOUBLE_QUOTE
			|| current->type == TOKEN_SINGLE_QUOTE)
		{
			num_tokens = 0;
			type = current->type;
			start = current;
			while (current->next && current->next->type != type)
			{
				current = current->next;
				num_tokens++;
			}
			if (current->next == NULL)
				return ;
			if (DEBUG)
				printf("Num tokens: %d\n", num_tokens);
			current = start;
			current = current->next;
			num_tokens--;
			current->value = ft_strjoin(current->value, "");
			while (num_tokens > 0)
			{
				current->value = ft_strjoin(current->value,
						current->next->value);
				if (current->next->next)
					current->next = current->next->next;
				else
					current->next = NULL;
				num_tokens--;
			}
		}
		current = current->next;
	}
}

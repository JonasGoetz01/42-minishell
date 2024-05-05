#include "../../inc/minishell.h"

void	retokenize(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;
	t_token	*new_token;
	int		i;
	char	**split;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_SINGLE_QUOTE
			|| current->type == TOKEN_DOUBLE_QUOTE)
		{
			temp = current;
			while (current->next && current->next->type != temp->type)
				current = current->next;
			if (current->next)
				current = current->next;
		}
		// remove extra spaces, only one matters
		else if (current->type == TOKEN_SPACE && current->next
			&& current->next->type == TOKEN_SPACE)
		{
			temp = current->next;
			current->next = temp->next;
			free(temp->value);
			free(temp);
		}
		// split words with spaces
		else if (current->type == TOKEN_WORD && ft_strchr(current->value, ' '))
		{
			split = ft_split(current->value, ' ');
			i = 0;
			while (split[i])
			{
				if (i == 0)
				{
					free(current->value);
					current->value = ft_strdup(split[i]);
				}
				else
				{
					new_token = create_token(TOKEN_WORD, ft_strdup(split[i]));
					new_token->next = current->next;
					current->next = new_token;
					current = current->next;
				}
				if (split[i + 1] != NULL)
				{
					new_token = create_token(TOKEN_SPACE, ft_strdup(" "));
					new_token->next = current->next;
					current->next = new_token;
					current = current->next;
				}
				i++;
			}
		}
		if (current)
			current = current->next;
	}
}

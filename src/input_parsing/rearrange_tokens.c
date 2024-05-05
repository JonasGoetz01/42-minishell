#include "../../inc/minishell.h"

bool	before_comes_word(t_token **token)
{
	t_token *current;

	current = *token;
	// prev_link_list(token);
	if (current->prev == NULL)
		return (false);
	while (current->prev != NULL)
	{
		if (current->prev->type == TOKEN_WORD)
			return (true);
		current = current->prev;
	}
	return (false);
}

// sometimes the tokens need to be rearranged
// example 1:
// echo < file.txt hello ... => echo hello ... < file.txt
// example 2:
// echo < file.txt hello ... && test => echo hello ... < file.txt && test
// example 3:
// < file.txt echo hello ... => echo hello ... < file.txt
// example 4:
// < file.txt echo hello ... && test => echo hello ... < file.txt && test
//
// For testing
// echo 1 && < test.txt echo 2 && echo 3
// echo 1 && < test.txt echo 2 && < test1.txt echo 3
// < test.txt echo 1
void	rearrange_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*redirect;
	t_token	*file;
	t_token	*after_file;
	t_token	*end;
	t_token *before_end;
	t_token *tmp;

	current = *tokens;
	prev_link_list(tokens);
	while (current != NULL && !(current->type == TOKEN_LESS
			|| current->type == TOKEN_DOUBLE_LESS
			|| current->type == TOKEN_GREATER
			|| current->type == TOKEN_DOUBLE_GREATER))
	{
		current = current->next;
	}
	if (current && (current->type == TOKEN_GREATER || current->type == TOKEN_DOUBLE_GREATER))
	{
		prev_link_list(tokens);
		if (!before_comes_word(&current))
		{			
			redirect = current;
			file = redirect;
			while (file->next && file->next->type == TOKEN_SPACE)
				file = file->next;
			if (!file->next || isOperator(*file->next))
				return ;
			if (file->next && (file->next->type == TOKEN_SINGLE_QUOTE || file->next->type == TOKEN_DOUBLE_QUOTE))
			{
				tmp = file->next;
				file->next = tmp->next;
				free(tmp->value);
				free(tmp);
				file->next = NULL;
				file = file->next;
				tmp = file->next;
				if (tmp->next)
					file->next = tmp->next;
				else
					file->next = NULL;
				free(tmp->value);
				free(tmp);
				tmp = NULL;
			}
			else if (file->next && file->next->type == TOKEN_WORD)
				file = file->next;
			after_file = file;
			while (after_file->next && after_file->next->type == TOKEN_SPACE)
				after_file = after_file->next;
			if (!after_file->next || isOperator(*after_file->next))
				return ;
			if (after_file->next)
				after_file = after_file->next;
			end = after_file;
			while (end->next && !isOperator(*end->next))
				end = end->next;
			if (end->next)
				before_end = end->prev;
			else
			{
				before_end = end;
				end = NULL;
			}
			prev_link_list(tokens);
			if (current->prev)
			{
				current = current->prev;
				current->next = after_file;
			}
			else
			{
				current = *tokens;
				*tokens = after_file;
			}
			prev_link_list(tokens);
			before_end->next = redirect;
			redirect->next = file;
			file->next = end;
		}
	}
}

//cmd > out after_file arg1 | cmd2
#include "../../inc/minishell.h"

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
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current != NULL && !(current->type == TOKEN_LESS
			|| current->type == TOKEN_DOUBLE_LESS
			|| current->type == TOKEN_GREATER
			|| current->type == TOKEN_DOUBLE_GREATER))
	{
		prev = current;
		current = current->next;
	}
	// If < is the first token
	// if (prev == NULL && current != NULL && current->next
	// 	&& current->next->type == TOKEN_WORD && current->next->next
	// 	&& current->next->next->type == TOKEN_WORD)
	// {
	// 	redirect = *tokens;
	// 	file = redirect->next;
	// 	after_file = file->next;
	// 	current = after_file;
	// 	*tokens = after_file;
	// 	while (current != NULL && current->type == TOKEN_WORD)
	// 		current = current->next;
	// 	while (after_file != NULL && after_file->next != NULL
	// 		&& after_file->next->type == TOKEN_WORD)
	// 		after_file = after_file->next;
	// 	file->next = after_file->next;
	// 	after_file->next = redirect;
	// 	if (file->next != NULL)
	// 		rearrange_tokens(&file->next);
	// }
	// else if (prev == NULL && current != NULL && current->next
	// 	&& current->next->type == TOKEN_WORD && !current->next->next)
	// {
	// 	redirect = *tokens;
	// 	file = redirect->next;
	// 	current = create_token(TOKEN_SPACE, ft_strdup(" "));
	// 	current->next = redirect;
	// 	*tokens = current;
	// }
	// // If < is not the first token
	// else if (current != NULL && (prev == NULL || (prev->type != TOKEN_WORD
	// 			&& prev->type != TOKEN_DOUBLE_QUOTE
	// 			&& prev->type != TOKEN_SINGLE_QUOTE)) && current->next
	// 	&& current->next->type == TOKEN_WORD && current->next->next
	// 	&& current->next->next->type == TOKEN_WORD)
	// {
	// 	redirect = current;
	// 	file = current->next;
	// 	after_file = file->next;
	// 	current = after_file;
	// 	while (current != NULL && current->type == TOKEN_WORD)
	// 		current = current->next;
	// 	if (prev != NULL)
	// 		prev->next = after_file;
	// 	else
	// 		(*tokens)->next = after_file;
	// 	while (after_file != NULL && after_file->next != NULL
	// 		&& after_file->next->type == TOKEN_WORD)
	// 		after_file = after_file->next;
	// 	file->next = after_file->next;
	// 	after_file->next = redirect;
	// 	if (file->next != NULL)
	// 		rearrange_tokens(&file->next);
	// }
	// > needs to be rearranged
	prev_link_list(tokens);
	if (current && (current->type == TOKEN_GREATER || current->type == TOKEN_DOUBLE_GREATER))
	{

	}
}

#include "../../inc/minishell.h"

bool	next_is_operator(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	{
		if (isOperator(*current))
			return (true);
	}
	return (false);
}

bool	next_is_word(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	{
		if (current->type == TOKEN_WORD)
			return (true);
	}
	return (false);
}

// check if all remining tokens are spaces
bool	next_is_newline(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	{
		if (current)
			return (false);
	}
	return (true);
}

bool	next_is_quotes(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	{
		if (current->type == TOKEN_SINGLE_QUOTE
			|| current->type == TOKEN_DOUBLE_QUOTE)
			return (true);
	}
	return (false);
}

bool	next_is_brackets(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	{
		if (current->type == TOKEN_BRACKET_L
			|| current->type == TOKEN_BRACKET_R)
			return (true);
	}
	return (false);
}

void	remove_spaces_before_arguments(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			prev = current;
			current = current->next;
			while (current && current->type == TOKEN_SPACE)
			{
				while (current->type == TOKEN_SPACE)
				{
					temp = current;
					prev->next = current->next;
					free(temp->value);
					free(temp);
					current = prev->next;
				}
			}
		}
		prev = current;
		if (current)
			current = current->next;
	}
}

void	remove_spaces_after_arguments(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	current = *tokens;
	while (current)
	{
		if (isOperator(*current))
		{
			while (current->next && current->next->type == TOKEN_SPACE)
			{
				temp = current->next;
				current->next = current->next->next;
				free(temp->value);
				free(temp);
			}
		}
		if (current)
			current = current->next;
	}
}

void	remove_spaces_at_beginning_end(t_token **tokens)
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
			if (prev == NULL || next_is_newline(current)
				|| next_is_operator(current))
			{
				if (prev == NULL)
					*tokens = current->next;
				else
					prev->next = current->next;
				temp = current;
				current = current->next;
				free(temp->value);
				free(temp);
				continue ;
			}
		}
		prev = current;
		if (current)
			current = current->next;
	}
}

/// @brief Remove all unused spaces from the token list
/// @param tokens
/// @return void
/// Main logic:
/// Spaces are not needed when:
/// 1. They are at the beginning of the line
/// 2. They are at the end of the line
/// 3. They are before or after arguments
///
/// Spaces are needed:
/// 1. Between arguments
/// 2. in a string
void	remove_unused_spaces(t_token **tokens)
{
	remove_spaces_before_arguments(tokens);
	remove_spaces_after_arguments(tokens);
	remove_spaces_at_beginning_end(tokens);
}

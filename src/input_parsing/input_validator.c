#include "../../inc/minishell.h"

// checks if the input is valid
// checks for parenthesis, quotes, and other special characters
// returns 0 if the input is valid, 1 if it is not
// if there is a quote, double quote inside a quote or double quote it gets
// ignored since it just gets printed and not used as a special character
int	validator(char *input)
{
	int	i;
	int	quote;
	int	dquote;
	int	parenthesis;

	i = 0;
	quote = 0;
	dquote = 0;
	parenthesis = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && i == 0 && quote == 0)
			dquote = !dquote;
		if (input[i] == '(' && i == 0 && dquote == 0 && quote == 0)
			parenthesis++;
		if (input[i] == ')' && i == 0 && dquote == 0 && quote == 0)
			parenthesis--;
		i++;
	}
	if (parenthesis != 0 || quote != 0 || dquote != 0)
		return (1);
	return (0);
}

int	input_validation(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	int		quote;
	int		dquote;
	int		parenthesis;

	current = *tokens;
	prev = NULL;
	quote = 0;
	dquote = 0;
	parenthesis = 0;
	while (current)
	{
		if (!prev && (current->type == TOKEN_PIPE))
			return (printf("Invalid input!\n"), 1);
		if (current->type == TOKEN_LESS && current->next
			&& current->next->type == TOKEN_GREATER)
			return (printf("Invalid input!\n"), 1);
		if (current->type == TOKEN_SINGLE_QUOTE && !dquote)
			quote = !quote;
		else if (current->type == TOKEN_DOUBLE_QUOTE && !quote)
			dquote = !dquote;
		else if (current->type == TOKEN_BRACKET_L)
			parenthesis++;
		else if (current->type == TOKEN_BRACKET_R)
			parenthesis--;
		prev = current;
		current = current->next;
	}
	if (parenthesis != 0 || quote != 0 || dquote != 0)
		return (printf("Invalid input!\n"), 1);
	return (0);
}

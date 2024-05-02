#include "../../inc/minishell.h"

t_token_type get_next_type(t_token *token)
{
	t_token *current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	if (current)
		return (current->type);
	return (TOKEN_WORD);
}

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
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
		if (input[i] == '(' && dquote == 0 && quote == 0)
			parenthesis++;
		if (input[i] == ')' && dquote == 0 && quote == 0)
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
		// if pipe comes after pipe
		if ((!prev && (current->type == TOKEN_PIPE)) 
			|| (current == *tokens && next_is_operator(current)))
		{
			while (current->type == TOKEN_SPACE)
				current = current->next;
			if (current->type == TOKEN_PIPE)
				return (ft_print_error("syntax error 1", NULL), 1);
		}
		// // if pipe comes after a operator
		// if (next_is_operator(current))
		// {
		// 	while (current->type == TOKEN_SPACE)
		// 		current = current->next;
		// 	if (!(current->type == TOKEN_PIPE) && next_is_operator(current->next))
		// 		return (ft_print_error("syntax error 2", NULL), 1);
		// }
		// if the first token is a pipe
		if ((current == *tokens) && (get_next_type(current) == TOKEN_PIPE))
			return (ft_print_error("syntax error 3", NULL), 1);
		// > needs word after it
		if ((current->type == TOKEN_GREATER || current->type == TOKEN_DOUBLE_GREATER) && ((current->next &&
				next_is_operator(current->next)) || next_is_newline(current->next)))
			return (ft_print_error("syntax error 4", NULL), 1);
		// < needs word after it
		if (current->type == TOKEN_LESS && ((current->next &&
				next_is_operator(current->next)) || next_is_newline(current->next)))
			return (ft_print_error("syntax error 5", NULL), 1);
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
		return (ft_print_error("syntax error 6", NULL), 1);
	return (0);
}

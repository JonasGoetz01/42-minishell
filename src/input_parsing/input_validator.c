/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:35 by vscode            #+#    #+#             */
/*   Updated: 2024/05/12 10:46:24 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool			first_is_pipe_second_operator(t_token **prev, t_token **current,
					t_token **tokens);
bool			pipe_after_pipe(t_token *current);
bool			redirect_has_no_file(t_token *current);
bool			no_file_for_indirect(t_token *current);
bool			ft_no_lim_heredoc(t_token *current);
bool			operator_has_no_right_side(t_token *current);
bool			empty_bracket(t_token *current);
bool			open_bracket_after_closing(t_token *current);
bool			check_invalids(t_token **tokens, t_token **prev,
					t_token **current);

t_token_type	get_next_type(t_token *token)
{
	t_token	*current;

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

void	handle_parenthesis_and_brackets(t_token **current, int *parenthesis,
		int *quote, int *dquote)
{
	if ((*current)->type == TOKEN_SINGLE_QUOTE && !dquote)
		*quote = !*quote;
	else if ((*current)->type == TOKEN_DOUBLE_QUOTE && !quote)
		*dquote = !*dquote;
	else if ((*current)->type == TOKEN_BRACKET_L)
		(*parenthesis)++;
	else if ((*current)->type == TOKEN_BRACKET_R)
		(*parenthesis)--;
}

void	initialize_vars(int *quote, int *dquote, int *parenthesis)
{
	*quote = 0;
	*dquote = 0;
	*parenthesis = 0;
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
	initialize_vars(&quote, &dquote, &parenthesis);
	while (current)
	{
		if (check_invalids(tokens, &prev, &current))
			return (ft_print_error("syntax error", NULL), 1);
		handle_parenthesis_and_brackets(&current, &parenthesis, &quote,
			&dquote);
		prev = current;
		current = current->next;
	}
	if (parenthesis != 0 || quote != 0 || dquote != 0)
		return (ft_print_error("syntax error", NULL), 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:50:43 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 13:43:55 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Print the tokens
void	print_tokens(t_token *tokens, t_global *global)
{
	if (DEBUG || (ft_get_env("DEBUG", global->envv) && ft_get_env("DEBUG",
				global->envv)[0] == '1'))
	{
		printf("Tokens:\n");
		while (tokens != NULL)
		{
			printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
			tokens = tokens->next;
		}
	}
}

// Check if the token is an operator
int	is_operator(t_token token)
{
	return (token.type == TOKEN_AMPERSAND || token.type == TOKEN_BRACKET_L
		|| token.type == TOKEN_BRACKET_R || token.type == TOKEN_DOUBLE_AMPERSAND
		|| token.type == TOKEN_DOUBLE_GREATER || token.type == TOKEN_DOUBLE_LESS
		|| token.type == TOKEN_DOUBLE_PIPE || token.type == TOKEN_GREATER
		|| token.type == TOKEN_LESS || token.type == TOKEN_PIPE);
}

void	free_token(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	current = *tokens;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->value);
		free(temp);
		temp = NULL;
	}
	free(*tokens);
	*tokens = NULL;
}

void	prev_link_list(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

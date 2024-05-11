/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:58:13 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 13:36:05 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_highest_token(t_token **highest_token, t_token **current_token)
{
	int	brackets_level;
	int	highest_token_brackets_level;

	highest_token_brackets_level = 0;
	brackets_level = 0;
	while ((*current_token) != NULL)
	{
		if ((*current_token)->type == TOKEN_BRACKET_L)
			brackets_level++;
		else if ((*current_token)->type == TOKEN_BRACKET_R)
			brackets_level--;
		if ((*highest_token) == NULL
			|| ((precedence(*(*current_token)) > precedence(*(*highest_token))
					&& (brackets_level <= highest_token_brackets_level)))
			|| (precedence(*(*current_token)) == precedence(*(*highest_token))
				&& brackets_level <= highest_token_brackets_level)
			|| (brackets_level < highest_token_brackets_level
				&& (*current_token)->type != TOKEN_BRACKET_L
				&& (*current_token)->type != TOKEN_BRACKET_R))
		{
			(*highest_token) = (*current_token);
			highest_token_brackets_level = brackets_level;
		}
		(*current_token) = (*current_token)->next;
	}
}

void	create_ast(t_ast_node **ast, t_ast_node **root, t_token **highest_token)
{
	if ((*ast) == NULL)
	{
		(*ast) = malloc(sizeof(t_ast_node));
		(*ast)->token = *highest_token;
		(*ast)->process = NULL;
		(*ast)->left = NULL;
		(*ast)->right = NULL;
		(*ast)->file_in = NULL;
		(*ast)->fd_in[0] = NULL;
		(*ast)->fd_in[1] = NULL;
		(*ast)->fd_out[0] = NULL;
		(*ast)->fd_out[1] = NULL;
		(*ast)->file_out = NULL;
		(*ast)->exit_status = -1;
		*root = *ast;
	}
}

void	skip_tokens(t_ast_node **ast, t_token **tokens, t_token **current_token)
{
	(*ast)->token = (*tokens);
	while ((*ast)->token->type == TOKEN_BRACKET_L
		|| (*ast)->token->type == TOKEN_BRACKET_R)
		(*ast)->token = (*ast)->token->next;
	(*current_token) = (*ast)->token;
	while ((*current_token)->next != NULL)
		(*current_token) = (*current_token)->next;
}

bool	handle_highest_token(t_ast_node **ast, t_token **highest_token,
		t_token **tokens, t_token **current_token)
{
	t_token	*prev_token;

	prev_token = NULL;
	if ((*highest_token)->type == TOKEN_WORD
		|| (*highest_token)->type == TOKEN_SPACE)
	{
		skip_tokens(ast, tokens, current_token);
		while ((*current_token)->type == TOKEN_BRACKET_L
			|| (*current_token)->type == TOKEN_BRACKET_R)
		{
			prev_token = (*ast)->token;
			while (prev_token->next != (*current_token))
				prev_token = prev_token->next;
			prev_token->next = NULL;
			free((*current_token)->value);
			if ((*current_token)->be_value)
				free((*current_token)->be_value);
			(*current_token)->be_value = NULL;
			free((*current_token));
			(*current_token) = NULL;
			(*current_token) = prev_token;
		}
		return (true);
	}
	return (false);
}

void	create_arms(t_token **right_arm, t_token **tokens,
		t_token **current_token, t_token **highest_token)
{
	(*current_token) = (*tokens);
	while ((*current_token)->next && (*current_token)->next != (*highest_token))
		(*current_token) = (*current_token)->next;
	(*current_token)->next = NULL;
	(*right_arm) = (*highest_token)->next;
}

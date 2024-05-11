/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:55:28 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 15:19:29 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_highest_token(t_token **highest_token, t_token **current_token);
void	create_ast(t_ast_node **ast, t_ast_node **root,
			t_token **highest_token);
void	skip_tokens(t_ast_node **ast, t_token **tokens,
			t_token **current_token);
bool	handle_highest_token(t_ast_node **ast, t_token **highest_token,
			t_token **tokens, t_token **current_token);
void	create_arms(t_token **right_arm, t_token **tokens,
			t_token **current_token, t_token **highest_token);

t_token	*last_is_bracket(t_token *tokens)
{
	t_token	*current;
	t_token	*ret;

	ret = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_BRACKET_R)
			ret = current;
		else if (current->type == TOKEN_SPACE)
			;
		else if (current->type == TOKEN_BRACKET_L)
			ret = NULL;
		else
			ret = NULL;
		current = current->next;
	}
	return (ret);
}

bool	second_open_bracket(t_token **tokens)
{
	t_token	*current;
	int		brackets_level;

	current = *tokens;
	brackets_level = 0;
	while (current)
	{
		if (current->type == TOKEN_BRACKET_L)
			brackets_level++;
		else if (current->type == TOKEN_BRACKET_R)
			brackets_level--;
		current = current->next;
	}
	if (brackets_level > 0)
		return (true);
	else
		return (false);
}

void	pt(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		printf("type: %d, value: %s\n", current->type, current->value);
		current = current->next;
	}
}

void	remove_bracktes_util(t_token **tokens, t_token **closing_bracket)
{
	prev_link_list(tokens);
	if ((*closing_bracket)->prev && (*closing_bracket)->next)
	{
		(*closing_bracket)->prev->next = (*closing_bracket)->next;
		free((*closing_bracket)->value);
		if ((*closing_bracket)->be_value)
			free((*closing_bracket)->be_value);
		free((*closing_bracket));
	}
	else if (!(*closing_bracket)->prev)
	{
		free_tokens(*tokens);
		*tokens = NULL;
	}
	else if (!(*closing_bracket)->next)
	{
		(*closing_bracket)->prev->next = NULL;
		free((*closing_bracket)->value);
		if ((*closing_bracket)->be_value)
			free((*closing_bracket)->be_value);
		free((*closing_bracket));
	}
}

void	free_open_bracket(t_token **opening_bracket, t_token **current)
{
	(*opening_bracket)->prev->next = *current;
	free((*opening_bracket)->value);
	if ((*opening_bracket)->be_value)
		free((*opening_bracket)->be_value);
	free((*opening_bracket));
}

// if the tokens have brackets at the beginning and end, remove them
void	remove_brackets(t_token **tokens)
{
	t_token	*current;
	t_token	*closing_bracket;
	t_token	*opening_bracket;

	current = *tokens;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	if (!current)
		return ;
	if (second_open_bracket(&(current)))
		return ;
	closing_bracket = last_is_bracket(current->next);
	if (current && current->type == TOKEN_BRACKET_L && closing_bracket
		&& closing_bracket->type == TOKEN_BRACKET_R)
	{
		prev_link_list(tokens);
		opening_bracket = current;
		current = current->next;
		if (opening_bracket->prev)
			free_open_bracket(&opening_bracket, &current);
		else
			*tokens = current;
		remove_bracktes_util(tokens, &closing_bracket);
	}
}

// walk through tokens and search for the highest precedence operator
// -> use precedence_node for that
// set the root of the ast to that operator
// walk through tokens again and set the left and right
// nodes of the root recursively
void	gen_ast(t_ast_node **root, t_token *tokens)
{
	t_token		*highest_token;
	t_token		*current_token;
	t_ast_node	*ast;
	t_token		*left_arm;
	t_token		*right_arm;

	highest_token = NULL;
	current_token = tokens;
	ast = *root;
	remove_brackets(&tokens);
	if (!tokens)
		return ;
	get_highest_token(&highest_token, &current_token);
	create_ast(&ast, root, &highest_token);
	if (handle_highest_token(&ast, &highest_token, &tokens, &current_token)
		|| highest_token->next == NULL)
		return ;
	create_arms(&right_arm, &tokens, &current_token, &highest_token);
	left_arm = tokens;
	ast->token->next = NULL;
	if (left_arm == highest_token)
		left_arm = NULL;
	gen_ast(&(ast->left), left_arm);
	gen_ast(&(ast->right), right_arm);
}

void	print_ast(t_ast_node **root, int level, t_global *global)
{
	t_ast_node	*ast;
	t_token		*token;
	int			i;

	i = 0;
	ast = *root;
	if (ast == NULL)
		return ;
	if (ft_is_debug(global))
	{
		print_ast(&(ast->right), level + 1, global);
		token = ast->token;
		while (token != NULL)
		{
			i = 0;
			while (i++ < level)
				printf("    ");
			printf("Type: %d, Value: %s Prio: %d\n", token->type, token->value,
				precedence_node(ast));
			token = token->next;
		}
		print_ast(&(ast->left), level + 1, global);
	}
}

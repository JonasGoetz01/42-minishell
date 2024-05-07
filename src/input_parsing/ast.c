/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:55:28 by vscode            #+#    #+#             */
/*   Updated: 2024/05/07 10:06:30 by vscode           ###   ########.fr       */
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

	if (!tokens)
		return ;
	highest_token = NULL;
	current_token = tokens;
	ast = *root;
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

void	print_ast(t_ast_node **root, int level)
{
	t_ast_node	*ast;
	t_token		*token;
	int			i;

	i = 0;
	ast = *root;
	if (ast == NULL)
		return ;
	if (DEBUG)
	{
		print_ast(&(ast->right), level + 1);
		token = ast->token;
		while (token != NULL)
		{
			while (i < level)
			{
				printf("    ");
				i++;
			}
			printf("Type: %d, Value: %s Prio: %d\n", token->type, token->value,
				precedence_node(ast));
			token = token->next;
		}
		print_ast(&(ast->left), level + 1);
	}
}

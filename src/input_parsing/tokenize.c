/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:25:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/22 14:10:22 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenize(const char *input, int *numTokens)
{
	const char	*delimiters = " ";
	char		*tokenStr;
	char		*token;
	t_token		*tokens;
	int			count;

	tokenStr = strdup(input);
	token = strtok(tokenStr, delimiters);
	tokens = NULL;
	count = 0;
	while (token != NULL)
	{
		tokens = realloc(tokens, (count + 1) * sizeof(t_token));
		tokens[count].value = strdup(token);
		if (strcmp(token, "|") == 0)
		{
			tokens[count].type = TOKEN_PIPE;
		}
		else if (strcmp(token, "<") == 0)
		{
			tokens[count].type = TOKEN_REDIRECT_IN;
		}
		else if (strcmp(token, ">") == 0)
		{
			tokens[count].type = TOKEN_REDIRECT_OUT;
		}
		else
		{
			tokens[count].type = TOKEN_WORD;
		}
		count++;
		token = strtok(NULL, delimiters);
	}
	*numTokens = count;
	free(tokenStr);
	return (tokens);
}

t_ast_node	*buildAST(t_token *tokens, int numTokens, int *depth)
{
	t_ast_node	*root;

	if (numTokens <= 0 || tokens == NULL)
	{
		return (NULL);
	}
	root = (t_ast_node *)malloc(sizeof(t_ast_node));
	root->type = tokens[0].type;
	root->value = strdup(tokens[0].value);
	root->left = NULL;
	root->right = NULL;
	if (numTokens > 1)
	{
		root->left = buildAST(tokens + 1, numTokens - 1, depth + 1);
	}
	return (root);
}

void	printAST(t_ast_node *root, int depth)
{
	if (root == NULL)
	{
		return ;
	}
	switch (root->type)
	{
	case TOKEN_WORD:
		printf("Command: %s\n", root->value);
		break ;
	case TOKEN_PIPE:
		printf("Pipe\n");
		break ;
	case TOKEN_REDIRECT_IN:
		printf("Redirect In (<)\n");
		break ;
	case TOKEN_REDIRECT_OUT:
		printf("Redirect Out (>)\n");
		break ;
	default:
		printf("Unknown\n");
	}
	printAST(root->left, depth + 1);
	printAST(root->right, depth + 1);
}

void	freeAST(t_ast_node *root)
{
	(void)root;
}
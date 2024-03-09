/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:25:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 14:33:55 by jgotz            ###   ########.fr       */
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
		if (strcmp(token, "+") == 0)
		{
			tokens[count].type = TOKEN_PLUS;
		}
		else if (strcmp(token, "-") == 0)
		{
			tokens[count].type = TOKEN_MINUS;
		}
		else if (strcmp(token, "*") == 0)
		{
			tokens[count].type = TOKEN_MULT;
		}
		else if (strcmp(token, "/") == 0)
		{
			tokens[count].type = TOKEN_DIV;
		}
		else if (strcmp(token, "(") == 0)
		{
			tokens[count].type = TOKEN_BRACKET_L;
		}
		else if (strcmp(token, ")") == 0)
		{
			tokens[count].type = TOKEN_BRACKET_R;
		}
		else
		{
			tokens[count].type = TOKEN_NUMBER;
			tokens[count].value = ft_atoi(token);
		}
		count++;
		token = strtok(NULL, delimiters);
	}
	*numTokens = count;
	free(tokenStr);
	return (tokens);
}

void	print_tokens(t_token *tokens, int numTokens)
{
	int	i;

	i = 0;
	while (i < numTokens)
	{
		switch (tokens[i].type)
		{
		case TOKEN_PLUS:
			printf("PLUS");
			break ;
		case TOKEN_MINUS:
			printf("MINUS");
			break ;
		case TOKEN_MULT:
			printf("MULT");
			break ;
		case TOKEN_DIV:
			printf("DIV");
			break ;
		case TOKEN_BRACKET_L:
			printf("BRACKET_L");
			break ;
		case TOKEN_BRACKET_R:
			printf("BRACKET_R");
			break ;
		case TOKEN_NUMBER:
			printf("NUMBER");
			break ;
		default:
			break ;
		}
		printf(" ");
		i++;
	}
	printf("\n");
}

t_token	*postfixFromTokens(t_token *tokens, int numTokens, int *postfixSize)
{
	t_stack	*stack;
	t_token	*postfix;
	int		postfixIndex;
	t_token	token;

	stack = createStack(numTokens);
	postfix = (t_token *)malloc(numTokens * sizeof(t_token));
	postfixIndex = 0;
	for (int i = 0; i < numTokens; i++)
	{
		token = tokens[i];
		switch (token.type)
		{
		case TOKEN_NUMBER:
			postfix[postfixIndex++] = token;
			break ;
		case TOKEN_PLUS:
		case TOKEN_MINUS:
		case TOKEN_MULT:
		case TOKEN_DIV:
			while (stack->size > 0 && (stack->array[stack->size
					- 1].type == TOKEN_PLUS || stack->array[stack->size
					- 1].type == TOKEN_MINUS || stack->array[stack->size
					- 1].type == TOKEN_MULT || stack->array[stack->size
					- 1].type == TOKEN_DIV))
			{
				postfix[postfixIndex++] = pop(stack);
			}
			push(stack, token);
			break ;
		case TOKEN_BRACKET_L:
			push(stack, token);
			break ;
		case TOKEN_BRACKET_R:
			while (stack->size > 0 && stack->array[stack->size
				- 1].type != TOKEN_BRACKET_L)
			{
				postfix[postfixIndex++] = pop(stack);
			}
			if (stack->size == 0)
			{
				fprintf(stderr, "Mismatched parentheses.\n");
				exit(EXIT_FAILURE);
			}
			pop(stack); // Discard the left bracket
			break ;
		default:
			fprintf(stderr, "Invalid token.\n");
			exit(EXIT_FAILURE);
		}
	}
	while (stack->size > 0)
	{
		if (stack->array[stack->size - 1].type == TOKEN_BRACKET_L
			|| stack->array[stack->size - 1].type == TOKEN_BRACKET_R)
		{
			fprintf(stderr, "Mismatched parentheses.\n");
			exit(EXIT_FAILURE);
		}
		postfix[postfixIndex++] = pop(stack);
	}
	*postfixSize = postfixIndex;
	free(stack->array);
	free(stack);
	return (postfix);
}

// 1 + 2 * 3 / ( 4 + 5 )

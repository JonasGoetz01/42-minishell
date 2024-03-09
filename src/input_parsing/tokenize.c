/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:25:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 13:41:13 by jgotz            ###   ########.fr       */
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
		// tokens[count].value = strdup(token);
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

void	print_stack(t_stack *stack)
{
	while (stack->next != NULL)
	{
		print_tokens((t_token *)stack->value, 1);
		stack = stack->next;
	}
}

int	isGreaterOrEqual(t_token *t1, t_token *t2)
{
	if (t2 == NULL)
		return (0);
	if (t1->type == TOKEN_DIV || t1->type == TOKEN_MULT)
	{
		return (1);
	}
	if (t1->type == TOKEN_MINUS || t1->type == TOKEN_PLUS)
	{
		if (t2->type == TOKEN_MINUS || t2->type == TOKEN_PLUS)
			return (1);
	}
	return (0);
}

int	isOperator(t_token *token)
{
	if (token->type == TOKEN_MINUS || token->type == TOKEN_PLUS
		|| token->type == TOKEN_MULT || token->type == TOKEN_DIV)
		return (1);
	return (0);
}

void	processToken(t_token *token, t_stack *postFix, t_stack *opStack)
{
	t_token	*top_element;
	t_token	*toPop;

	if (token->type == TOKEN_NUMBER)
		add(postFix, token);
	if (isOperator(token))
	{
		top_element = (t_token *)top(opStack)->value;
		while (isGreaterOrEqual(token, top_element))
		{
			toPop = (t_token *)pop(opStack)->value;
			add(postFix, toPop);
			top_element = (t_token *)top(opStack)->value;
		}
		add(opStack, token);
		if (token->type == TOKEN_BRACKET_L)
			add(opStack, token);
		if (token->type == TOKEN_BRACKET_R)
		{
			while (((t_token *)top(opStack)->value)->type != TOKEN_BRACKET_L)
			{
				toPop = (t_token *)pop(opStack)->value;
				add(postFix, toPop);
			}
			pop(opStack);
		}
	}
}

t_stack	*toPostFix(t_token *tokens, int numTokens)
{
	int		i;
	t_stack	*postFix;
	t_stack	*opStack;
	t_token	*token;
	t_stack	*op;

	postFix = malloc(sizeof(t_stack));
	opStack = malloc(sizeof(t_stack));
	postFix->value = NULL;
	opStack->value = NULL;
	for (i = 0; i < numTokens; i++)
	{
		token = &tokens[i];
		processToken(token, postFix, opStack);
	}
	while (stack_len(opStack) > 0)
	{
		op = pop(opStack);
		add(postFix, op->value);
	}
	return (postFix);
}

// 1 + 2 * 3 / ( 4 + 5 )
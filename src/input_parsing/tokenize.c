/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:25:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/13 15:36:52 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenize(const char *input)
{
	const char		*delimiters = "+-*/()";
	t_token			*tokens;
	t_token			*current;
	char			*value;
	t_token_type	type;
	t_token			*new_token;

	tokens = NULL;
	current = NULL;
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == ' ' && (input[i - 1] == '\'' || input[i - 1] == '\"'
				|| input[i + 1] == '\'' || input[i + 1] == '\"'))
		{
			continue ;
		}
		else if (strchr(delimiters, input[i]) != NULL || !isdigit(input[i + 1])
			|| input[i] == ' ')
		{
			value = malloc(2 * sizeof(char));
			value[0] = input[i];
			value[1] = '\0';
			switch (input[i])
			{
			case '+':
				type = TOKEN_PLUS;
				break ;
			case '-':
				type = TOKEN_MINUS;
				break ;
			case '*':
				type = TOKEN_MULT;
				break ;
			case '/':
				type = TOKEN_DIV;
				break ;
			case '(':
				type = TOKEN_BRACKET_L;
				break ;
			case ')':
				type = TOKEN_BRACKET_R;
				break ;
			default:
				type = TOKEN_NUMBER;
			}
			new_token = create_token(type, value);
			if (new_token != NULL)
			{
				if (tokens == NULL)
				{
					tokens = new_token;
					current = tokens;
				}
				else
				{
					current->next = new_token;
					current = current->next;
				}
			}
		}
		else
		{
			value = malloc(sizeof(char));
			value[0] = input[i];
			for (int j = i + 1; isdigit(input[j]); j++)
			{
				value = realloc(value, (j - i + 2) * sizeof(char));
				value[j - i] = input[j];
				value[j - i + 1] = '\0';
				i = j;
			}
			new_token = create_token(TOKEN_NUMBER, value);
			if (new_token != NULL)
			{
				if (tokens == NULL)
				{
					tokens = new_token;
					current = tokens;
				}
				else
				{
					current->next = new_token;
					current = current->next;
				}
			}
		}
	}
	return (tokens);
}

// Spaces should only stay there if they are after a quote or double quote
void	remove_unused_spaces(t_token *tokens)
{
	t_token	*prev;
	t_token	*current;
	t_token	*temp;

	prev = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_NUMBER && strcmp(current->value, " ") == 0)
		{
			// If the space is after a left bracket, leave it,
			// otherwise, remove it from the tokens
			if (prev != NULL && prev->type == TOKEN_BRACKET_L)
			{
				prev = current;
				current = current->next;
			}
			else
			{
				temp = current;
				if (prev == NULL)
				{ // if current is the head
					tokens = current->next;
					current = current->next;
				}
				else
				{
					prev->next = current->next;
					current = current->next;
				}
				free(temp->value);
				free(temp);
				continue ; // Skip moving current pointer forward
			}
		}
		prev = current;
		current = current->next;
	}
}

void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n");
	while (tokens != NULL)
	{
		printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	print_tokens_value(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_NUMBER)
		{
			printf("%s", current->value);
		}
		else
		{
			switch (current->type)
			{
			case TOKEN_PLUS:
				printf("+");
				break ;
			case TOKEN_MINUS:
				printf("-");
				break ;
			case TOKEN_MULT:
				printf("*");
				break ;
			case TOKEN_DIV:
				printf("/");
				break ;
			case TOKEN_BRACKET_L:
				printf("(");
				break ;
			case TOKEN_BRACKET_R:
				printf(")");
				break ;
			default:
				break ;
			}
		}
		current = current->next;
	}
	printf("\n");
}

int	isOperator(t_token token)
{
	return (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS
		|| token.type == TOKEN_MULT || token.type == TOKEN_DIV);
}

int	precedence(t_token token)
{
	switch (token.type)
	{
	case TOKEN_PLUS:
	case TOKEN_MINUS:
		return (1);
	case TOKEN_MULT:
	case TOKEN_DIV:
		return (2);
	default:
		return (0); // Assuming parentheses have the highest precedence
	}
}

t_token	*postfixFromTokens(t_token *tokens)
{
	t_stack	*stack;
	t_token	*postfix;
	t_token	*current;

	stack = createStack(token_count(tokens));
	postfix = NULL;
	current = tokens;
	while (current != NULL)
	{
		switch (current->type)
		{
		case TOKEN_NUMBER:
			append_token(&postfix, create_token(TOKEN_NUMBER, current->value));
			break ;
		case TOKEN_PLUS:
		case TOKEN_MINUS:
		case TOKEN_MULT:
		case TOKEN_DIV:
			while (stack->size > 0 && isOperator(peek(stack))
				&& precedence(*current) <= precedence(peek(stack)))
			{
				append_token(&postfix, create_token(peek(stack).type,
						peek(stack).value));
				pop(stack);
			}
			push(stack, *current);
			break ;
		case TOKEN_BRACKET_L:
			push(stack, *current);
			break ;
		case TOKEN_BRACKET_R:
			while (stack->size > 0 && peek(stack).type != TOKEN_BRACKET_L)
			{
				append_token(&postfix, create_token(peek(stack).type,
						peek(stack).value));
				pop(stack);
			}
			if (stack->size == 0 || peek(stack).type != TOKEN_BRACKET_L)
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
		current = current->next;
	}
	while (stack->size > 0)
	{
		if (peek(stack).type == TOKEN_BRACKET_L
			|| peek(stack).type == TOKEN_BRACKET_R)
		{
			fprintf(stderr, "Mismatched parentheses.\n");
			exit(EXIT_FAILURE);
		}
		append_token(&postfix, create_token(peek(stack).type,
				peek(stack).value));
		pop(stack);
	}
	freeStack(stack);
	return (postfix);
}

// 1 + 2 * 3 / ( 4 + 5 )

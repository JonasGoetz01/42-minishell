/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:38 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:24:39 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "helpers.h"

// t_token	**create_token_list(int count, ...)
// {
// 	va_list			args;
// 	t_token			**head;
// 	t_token			*current;
// 	char			*value;
// 	t_token			*token;
// 	t_token_type	type;

// 	va_start(args, count);
// 	head = malloc(sizeof(t_token));
// 	*head = NULL;
// 	current = NULL;
// 	for (int i = 0; i < count; ++i)
// 	{
// 		type = va_arg(args, t_token_type); // Get the type of the argument
// 		value = va_arg(args, char *);
// 		token = malloc(sizeof(t_token));
// 		if (!token)
// 			return (NULL);
// 		token->type = type; // Set the type of the token
// 		token->value = ft_strdup(value);
// 		token->next = NULL;
// 		if (!(*head))
// 		{
// 			*head = token;
// 			current = token;
// 		}
// 		else
// 		{
// 			current->next = token;
// 			current = current->next;
// 		}
// 	}
// 	va_end(args);
// 	return (head);
// }

// void	free_token_list(t_token **head)
// {
// 	t_token *current;
// 	t_token *next;

// 	current = *head;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// 	free(head);
// }
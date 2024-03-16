/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:03:16 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/11 20:00:17 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// checks if the input is valid
// checks for parenthesis, quotes, and other special characters
// returns 0 if the input is valid, 1 if it is not
// if there is a quote, double quote inside a quote or double quote it gets
// ignored since it just gets printed and not used as a special character
int	validator(char *input)
{
	int i;
	int quote;
	int dquote;
	int parenthesis;

	i = 0;
	quote = 0;
	dquote = 0;
	parenthesis = 0;
	while (input[i])
	{
		if (input[i] == '(')
			parenthesis++;
		if (input[i] == ')')
			parenthesis--;
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	if (parenthesis != 0 || quote != 0 || dquote != 0)
		return (1);
	return (0);
}
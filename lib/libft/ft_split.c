/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:54:28 by jgotz             #+#    #+#             */
/*   Updated: 2023/10/23 15:58:12 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

int	check_res(char **result, int i)
{
	if (!result[i])
	{
		while (--i >= 0)
			free(result[i]);
		free(result);
		return (0);
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	int		words_count;
	char	**result;
	int		word_len;
	int		i;

	i = 0;
	words_count = count_words(s, c);
	result = (char **)ft_calloc(words_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (i < words_count)
	{
		while (*s && *s == c)
			s++;
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		result[i] = ft_substr(s, 0, word_len);
		if (check_res(result, i) == 0)
			return (NULL);
		s += word_len;
		i++;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;
// 	char	**strs;
// 	int		i;

// 	i = 0;
// 	str = "Hello world!";
// 	strs = ft_split(str, ' ');
// 	while (i < 2)
// 	{
// 		printf("%s\n", strs[i]);
// 		i++;
// 	}
// }

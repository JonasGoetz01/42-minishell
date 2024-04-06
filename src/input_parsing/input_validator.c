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
		if (input[i] == '(' && i > 0 && input[i - 1] != '\\' && dquote == 0
			&& quote == 0)
			parenthesis++;
		if (input[i] == ')' && i > 0 && input[i - 1] != '\\' && dquote == 0
			&& quote == 0)
			parenthesis--;
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && i > 0 && input[i - 1] != '\\' && quote == 0)
			dquote = !dquote;
		if (input[i] == '\\' && !input[i + 1])
			return (1);
		i++;
	}
	if (parenthesis != 0 || quote != 0 || dquote != 0)
		return (1);
	return (0);
}
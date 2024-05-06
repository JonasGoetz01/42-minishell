#include "../../inc/minishell.h"

static char	*ft_build_prompt_help(void)
{
	char	*pwd;
	char	*prompt;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	prompt = ft_strdup(KBLU);
	if (prompt == NULL)
		return (free(pwd), NULL);
	tmp = ft_strjoin(prompt, KBLU);
	free(prompt);
	if (tmp == NULL)
		return (free(pwd), NULL);
	prompt = ft_strjoin(tmp, pwd);
	free(pwd);
	free(tmp);
	return (prompt);
}

char	*ft_build_prompt(void)
{
	char	*prompt;
	char	*temp;

	prompt = ft_build_prompt_help();
	if (prompt == NULL)
		return (NULL);
	temp = ft_strjoin(prompt, KGRN);
	free(prompt);
	if (temp == NULL)
		return (NULL);
	prompt = ft_strjoin(temp, " ❯ ");
	free(temp);
	if (prompt == NULL)
		return (NULL);
	temp = ft_strjoin(prompt, KNRM);
	free(prompt);
	return (temp);
}

#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = SIGNAL_INT;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_signal = SIGNAL_INT;
}

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

void	handle_exec(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("QUIT\n", STDOUT_FILENO);
	g_signal = SIGNAL_INT;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	ft_putstr_fd("^C\n", STDOUT_FILENO);
	g_signal = SIGNAL_INT;
}

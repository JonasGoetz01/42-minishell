#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// make sure nothing happens when ctrl+\ is pressed
void	handle_sigquit(int sig)
{
	struct sigaction	act;

	(void)sig;
	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

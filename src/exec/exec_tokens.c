#include "../../inc/minishell.h"

void	ft_execute_nodes(t_ast_node *node, t_ast_node *ast, bool wait,
		t_global *global)
{
	t_exec_flags	exec_flags;

	if (!node || global->should_exit || global->exit_status > 128)
		return ;
	exec_flags.wait = wait;
	exec_flags.next_wait = wait;
	exec_flags.exit_on_err = false;
	exec_flags.tok_typ = -1;
	exec_flags.ast = ast;
	if (!ft_exec_tokens_loop(node, node->token, &exec_flags, global))
		return ;
	ft_execute_nodes(node->left, ast, exec_flags.next_wait, global);
	ft_set_right_exit_code(node, global);
	if (exec_flags.exit_on_err && global->exit_status >= 1)
		return ;
	if (exec_flags.tok_typ == TOKEN_DOUBLE_PIPE && global->exit_status == 0)
		return ;
	ft_execute_nodes(node->right, ast, exec_flags.next_wait, global);
	if (exec_flags.wait)
		ft_wait_for_processes(node, global);
	ft_set_right_exit_code(node, global);
}

void	ft_exec_all(t_ast_node *node, t_global *global)
{
	global->exit_status = 0;
	signal(SIGINT, handle_exec);
	signal(SIGQUIT, handle_exec);
	print_ast(&node, 0, global);
	ft_org_tokens(node);
	if (ft_is_debug(global))
		printf("-----\n");
	print_ast(&node, 0, global);
	ft_execute_nodes(node, node, true, global);
	ft_close_all_fds(global);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

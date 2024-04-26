#include "../../inc/minishell.h"

void	ft_execute_nodes(t_ast_node *node, bool wait, t_global *global)
{
	t_token_type	type;
	t_exec_flags	exec_flags;

	if (!node)
		return ;
	exec_flags.wait = wait;
	exec_flags.next_wait = wait;
	exec_flags.exit_on_err = false;
	type = ft_exec_tokens_loop(node, node->token, &exec_flags, global);
	ft_execute_nodes(node->left, exec_flags.next_wait, global);
	ft_set_right_exit_code(node, global);
	if (exec_flags.exit_on_err && global->exit_status >= 1)
		return ;
	if (type == TOKEN_DOUBLE_PIPE && global->exit_status == 0)
		return ;
	ft_execute_nodes(node->right, exec_flags.next_wait, global);
	if (exec_flags.wait)
		ft_wait_for_processes(node, global);
	ft_set_right_exit_code(node, global);
}

void	ft_exec_all(t_ast_node *node, t_global *global)
{
	ft_org_tokens(node);
	print_ast(&node, 0);
	ft_execute_nodes(node, true, global);
	ft_close_all_fds(global);
}

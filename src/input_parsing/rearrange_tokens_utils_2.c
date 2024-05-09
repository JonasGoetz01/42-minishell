/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:57:31 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 10:38:47 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_h(t_rearrange_helper *h)
{
	h->before_end->next = h->redirect;
	h->redirect->next = h->file;
	h->file->next = h->end;
}

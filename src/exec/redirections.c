/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   redirections.c                                     ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/11/01 22:00:34 by nomu                    ██║███████╗      */
/*   Updated: 2023/11/30 20:39:11 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/token.h"

static void	init_redir_vars(t_redir_vars *redir_vars, t_token_list *tokens)
{
	redir_vars->head = NULL;
	redir_vars->current = NULL;
	redir_vars->token_cursor = tokens;
	redir_vars->argument = NULL;
}

t_redir_list	*ft_new_redir_node(t_garbage_collector *gc, char *argument,
		t_token_type type)
{
	t_redir_list	*new_node;

	new_node = gc_malloc(gc, sizeof(t_redir_list));
	if (!new_node)
		return (NULL);
	new_node->file_name = argument;
	new_node->delimiter = argument;
	new_node->text = argument;
	new_node->heredoc_tmp = "heredoc_tmp";
	new_node->hd_parse = 0;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_redir_to_list(t_garbage_collector *gc, char *redir,
		t_redir_vars *redir_vars, t_token_type type)
{
	if (!redir_vars->head)
	{
		redir_vars->head = ft_new_redir_node(gc, redir, type);
		redir_vars->current = redir_vars->head;
	}
	else
	{
		redir_vars->current->next = ft_new_redir_node(gc, redir, type);
		redir_vars->current = redir_vars->current->next;
	}
}

t_redir_list	*ft_build_redir_lst(t_minishell *shell, t_token_list **tokens)
{
	t_redir_vars	redir_vars;

	init_redir_vars(&redir_vars, *tokens);
	while (redir_vars.token_cursor
		&& redir_vars.token_cursor->token.type != PIPE)
	{
		if (ft_is_redir(redir_vars.token_cursor->token.type))
		{
			redir_vars.argument = ft_gc_strdup(shell->gc,
					redir_vars.token_cursor->next->token.value);
			ft_add_redir_to_list(shell->gc, redir_vars.argument, &redir_vars,
				redir_vars.token_cursor->token.type);
		}
		if (redir_vars.token_cursor->prev
			&& redir_vars.token_cursor->prev->token.type == HEREDOC
			&& redir_vars.token_cursor->token.expand_hd != 1)
		{
			redir_vars.current->hd_parse = 1;
		}
		redir_vars.token_cursor = redir_vars.token_cursor->next;
	}
	shell->exec->redir_list = redir_vars.head;
	return (redir_vars.head);
}

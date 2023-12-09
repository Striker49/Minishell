/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:43:01 by nomu              #+#    #+#             */
/*   Updated: 2023/12/04 16:00:44 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef PRINT_H
# define PRINT_H

/*--- LIBRARIES ---*/

# include "minishell.h"

/*--- MAIN DATA STRUCTURES ---*/

typedef struct s_token_list		t_token_list;
typedef struct s_env_list		t_env_list;
typedef struct s_command_list	t_command_list;
typedef struct s_redir_list		t_redir_list;

/* --- PRINT FUNCTIONS --- */

void							ft_print_redirections(t_redir_list *redir_head);
void							ft_print_minishell_header(void);
void							ft_print_tokens(t_token_list *head);
void							ft_print_command_list(t_command_list *head);
void							ft_print_env(t_env_list *head);
void							ft_print_redir_list(t_redir_list *head);
void							print_err_msg(const char *prefix,
									const char *input,
									const char *suffix);

#endif

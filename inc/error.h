/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   error.h                                            ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/23 17:17:54 by seroy                   ██║███████╗      */
/*   Updated: 2023/11/30 19:44:57 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef ERROR_H
# define ERROR_H

/*--- LIBRARIES ---*/

# include "minishell.h"

/* --- MAIN DATA STRUCTURES --- */

typedef struct s_minishell	t_minishell;

typedef struct s_errno
{
	int						fd;
	int						exit_code;
}							t_errno;

/* --- ERROR HANDELING FUNCTIONS --- */

void						ft_handle_errno(t_minishell *shell, int flag);
void						ft_print_error_msg(t_minishell *shell, int flag);

#endif

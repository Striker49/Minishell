/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   syntax.h                                           ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/22 23:40:02 by nomu                    ██║███████╗      */
/*   Updated: 2023/11/29 19:37:59 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef SYNTAX_H
# define SYNTAX_H

/*--- LIBRARIES ---*/

# include "minishell.h"

/* --- MAIN DATA STRUCTURES --- */

typedef struct s_token_list	t_token_list;

char						ft_last_quote(char *string);
int							ft_is_valid_syntax(t_token_list *tokens);
int							validate_pipes(t_token_list *tokens);
int							validate_redirections(t_token_list *tokens);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   token.h                                            ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/20 20:08:29 by nomu                    ██║███████╗      */
/*   Updated: 2023/11/29 19:38:43 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef TOKEN_H
# define TOKEN_H

/*--- LIBRARIES ---*/

# include "minishell.h"
# include <unistd.h>

/* --- MAIN DATA STRUCTURES --- */

typedef struct s_garbage_collector	t_garbage_collector;

typedef enum e_token_type
{
	ERROR,
	PIPE,
	ALPHA,
	OUTFILE,
	INFILE,
	APPEND,
	HEREDOC,
}									t_token_type;

typedef struct s_token
{
	char							*value;
	int								len;
	int								expand_hd;
	t_token_type					type;
}									t_token;

typedef struct s_token_list
{
	t_token							token;
	struct s_token_list				*next;
	struct s_token_list				*prev;
	int								len;

}									t_token_list;

typedef struct s_tokenizer
{
	size_t							i;
	size_t							len;
	char							*prompt;
	t_token_list					*current;
	t_token_list					*head;
	t_garbage_collector				*gc;
}									t_tokenizer;

int									ft_is_redir(t_token_type type);
void								handle_single_quotes(t_tokenizer *tk);
void								handle_double_quotes(t_tokenizer *tk);
void								handle_pipe_token(t_tokenizer *tk);
void								handle_append_token(t_tokenizer *tk,
										size_t start);
void								handle_heredoc_token(t_tokenizer *tk,
										size_t start);
void								handle_outfile_token(t_tokenizer *tk,
										size_t start);
void								handle_infile_token(t_tokenizer *tk,
										size_t start);
void								handle_alpha(t_tokenizer *tk);
void								handle_delimiter(t_tokenizer *tk);
void								ft_init_tk_varaibles(t_minishell *shell,
										t_tokenizer *tk);
void								add_token_to_list(t_tokenizer *tk,
										t_token token);
t_token_list						*tokenizer(t_minishell *shell,
										char *prompt);
t_token_list						*ft_is_last_token(t_token_list *head);
t_token_list						*new_token_node(t_tokenizer *tk,
										t_token token);
t_token								ft_build_token(t_tokenizer *tk, char *start,
										size_t len, t_token_type type);
int									ft_count_token_type(t_token_list *head,
										t_token_type type);
#endif

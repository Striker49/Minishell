/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:29:41 by nomu              #+#    #+#             */
/*   Updated: 2023/12/06 11:48:09 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef PARSING_H
# define PARSING_H

/*--- LIBRARIES ---*/

# include "minishell.h"

/* --- MAIN DATA STRUCTURES --- */

typedef struct s_env_list	t_env_list;
typedef struct s_token_list	t_token_list;
typedef struct s_redir_list	t_redir_list;

typedef struct s_quotes
{
	int						i;
	int						j;
	int						len;
	int						inside_single_quote;
	int						inside_double_quote;
	char					*result;
}							t_quotes;

/* --- PARSING FUNCTIONS --- */
int							count_char(const char *input, char ch);
int							ft_parse_input(char *prompt);
int							ft_is_delimiter(int c);
int							ft_validate_quotes(t_minishell *shell,
								char *prompt);
int							ft_is_valid_quotes(char *string);
void						expand_dollar(t_minishell *shell,
								t_token_list *tokens,
								t_env_list *env_lst);
void						ft_find_dollar_sign(t_garbage_collector *gc,
								t_token_list **tokens, t_env_list *env_lst,
								t_minishell *shell);
char						*parse_quotes(t_garbage_collector *gc, char *input);
t_redir_list				*ft_parse_hd(t_minishell *shell,
								t_redir_list *redir);
void						replace_vars(t_minishell *shell, 
								t_token_list **current);
char						*ft_expand_err(t_minishell *shell, t_token_list 
								*current, int i);
char						*set_variable(t_minishell *shell, t_token_list 
								**current, int *start, int *i);

#endif

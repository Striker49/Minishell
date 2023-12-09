/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   env.h                                              ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/25 13:44:12 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/29 19:42:21 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef ENV_H
# define ENV_H

/*--- LIBRARIES ---*/

# include "minishell.h"

/* --- MAIN DATA STRUCTURES --- */

typedef struct s_garbage_collector	t_garbage_collector;
typedef struct s_minishell			t_minishell;

typedef struct s_var
{
	char							*key;
	char							*value;
	int								v_len;
	int								k_len;
}									t_var;

typedef struct s_env_list
{
	char							*elem;
	t_var							*env_var;
	struct s_env_list				*next;
	struct s_env_list				*prev;
}									t_env_list;

char				**env_list_to_arr(t_minishell *shell,
						t_garbage_collector *gcn,
						t_env_list *head);
void				ft_add_elem_to_end_of_list(t_garbage_collector *gc,
						t_env_list **head,
						char *env_str);
t_env_list			*ft_create_env_node(t_garbage_collector *gc,
						char *env_var);
void				ft_add_node_to_list(t_garbage_collector *gc,
						t_env_list **head,
						t_env_list **current,
						char *env_str);
t_env_list			*ft_build_env(t_garbage_collector *gc,
						char **envp);
void				duplicate_env(t_garbage_collector *gc,
						t_minishell *shell,
						char **envp);
int					count_key_len(char *env_elem);
int					count_value_len(char *env_elem);
t_var				*find_key(char *var, int var_len,
						t_env_list *env_lst);
char				*ft_get_env_key(t_garbage_collector *gc,
						char *env_elem);
char				*ft_get_env_value(t_garbage_collector *gc,
						char *env_elem);
void				ft_pwd(t_minishell *shell);
// char								**env_list_to_arr(t_minishell *shell)

#endif

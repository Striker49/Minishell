/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:22:25 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 19:36:44 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef EXEC_H
# define EXEC_H

/*--- LIBRARIES ---*/

# include "minishell.h"
# include "token.h"
# include <signal.h>
# include <termios.h>

/* --- MAIN DATA STRUCTURES --- */

typedef struct s_garbage_collector	t_garbage_collector;
typedef struct s_token_list			t_token_list;
typedef struct s_env_list			t_env_list;

typedef struct s_redir_list
{
	char							*delimiter;
	char							*file_name;
	char							*text;
	char							*heredoc_tmp;
	int								fd;
	int								hd_parse;
	t_token_type					type;
	struct s_redir_list				*next;

}									t_redir_list;

typedef struct s_redir_vars
{
	t_redir_list					*head;
	t_redir_list					*current;
	t_token_list					*token_cursor;
	char							*argument;

}									t_redir_vars;

typedef struct s_command_list
{
	int								index;
	int								pipe_fd[2];
	char							**cmd;
	struct s_redir_list				*redir_head;
	struct s_command_list			*next;
}									t_command_list;

typedef struct s_cmd_vars
{
	t_command_list					*current_cmd;
	t_command_list					*head_cmd;
	t_token_list					*token_cursor;
	int								index;
	t_redir_list					*redir_list;
	char							**cmd;
}									t_cmd_vars;

typedef struct s_executor
{
	char							*bin_path;
	t_redir_list					*redir_list;
	t_command_list					*command_list;
	int								pipe_fd[2];
	int								pipe_index;
	char							**table;
	char							buffer[1024];
	pid_t							*child_pid;
	pid_t							last_pid;
	int								child_nbr;

}									t_executor;

/* --- REDIRECTIONS --- */
int								ft_is_redir(t_token_type type);
int								ft_redir_switch(t_redir_list *redir_list);
t_redir_list					*ft_build_redir_lst(t_minishell *shell,
									t_token_list **tokens);
int								ft_exec_redir(t_minishell *shell,
									t_redir_list *redir_list);
void							ft_add_redir_to_list(t_garbage_collector *gc,
									char *redir,
									t_redir_vars *redir_vars,
									t_token_type type);
t_redir_list					*ft_new_redir_node(t_garbage_collector *gc,
									char *argument,
									t_token_type type);
int								handle_heredoc(t_minishell *shell,
									t_redir_list *redir);
int								handle_append(t_redir_list *redir);
int								handle_outfile(t_redir_list *redir);
int								handle_infile(t_redir_list *redir);

/* --- COMMANDS --- */
int								ft_count_commands(t_command_list *cmds);
void							init_cmd_vars(t_cmd_vars *cmd_vars,
									t_token_list *tokens);
t_command_list					*ft_build_commands(t_minishell *shell,
									t_token_list *tokens);
char							**ft_split_command(t_minishell *shell,
									t_token_list **token_ptr);
void							ft_add_cmd_to_list(t_garbage_collector *gc,
									char **cmd_table,
									t_cmd_vars *cmd_vars);
t_command_list					*ft_new_cmd_node(t_garbage_collector *gc,
									char **cmd_table,
									int index,
									t_redir_list *redir_head);
void							ft_exec_command(t_garbage_collector *gc,
									t_executor *exec,
									char **envp,
									t_command_list *cmd_node);

/* --- TOKENIZER --- */
char							**ft_tokens_to_str(t_garbage_collector *gc,
									t_token_list *tokens);
int								ft_count_tokens(t_token_list *tokens);
void							execute_child_logic(t_minishell *shell,
									t_command_list *cmd_node,
									char **envp,
									int b_flag);
void							execute_parent_logic(t_minishell *shell,
									t_executor *exec,
									t_command_list *cmd_node);
void							read_from_pipe(t_executor *exec,
									ssize_t *bytes_read);
int								setup_pipe(int *pipe_fd);
pid_t							create_child_process(t_executor *exec);
int								validate_path(t_minishell *shell,
									char **cmd);

/* --- SIGNALS --- */
void							interrupt(int sig);
void							interrupt2(int sig);
void							interrupt_hd(int sig);
void							quit(int sig);
void							do_nothing(int sig);
void							deactivate_ctrl(struct termios term);

/* --- BUILTINS --- */

void							update_env_elem(t_minishell *shell,
									t_env_list *elem, char *value, 
									char **var_table);
int								print_all_vars(t_minishell *shell,
									char **envp,
									t_token_list *current);
char							**sort_string_tab(char **tab,
									unsigned int size);
void							print_table(char **arr, int size);
char							*quote_substring(t_garbage_collector *gcn,
									char *input);
void							ft_unset(t_minishell *shell,
									t_command_list *command_list);
int								ft_export(t_minishell *shell, char **table);
void							ft_exec_builtin(t_minishell *shell,
									int flag,
									t_command_list *cmd_cursor);
void							ft_env(t_minishell *shell,
									t_command_list *command_list,
									t_env_list *env);
int								ft_is_builtin(char *cmd);
int								ft_cd(t_minishell *shell,
									t_command_list *command_list);
t_env_list						*find_env_elem(t_minishell *shell,
									char *var);
void							ft_echo(t_minishell *shell,
									t_command_list *command_list);
int								ft_is_valid_export_var(t_minishell *shell,
									char *string);
int								ft_is_valid_var_format(int c);
char							*find_path(char **envp);

void							handle_child_process_completion(t_minishell 
									*shell, int status);
void							ft_exec_loop(t_minishell *shell);
void							ft_init_exec_process(t_minishell *shell);
void							ft_process_commands(t_minishell *shell);
int								ft_process_loop(t_minishell *shell);
int								is_builtin_command(t_command_list *cmd_cursor);
void							execute_builtin_command(t_minishell *shell,
									t_command_list *cmd_cursor);
void							ft_attribute_pipes_fd(t_minishell *shell,
									t_command_list *cmd_cursor,
									int b_flag);
void							ft_execute(t_minishell *shell,
									t_command_list *cmd_cursor,
									int b_flag);
void							handle_child_absence_and_redirections(
									t_minishell *shell, int *r_flag,
									t_command_list *cmd_cursor);
int								ft_check_err_cases(t_minishell *shell,
									t_command_list *cmd_cursor);
void							handle_child_process_logic(t_minishell *shell,
									t_command_list *cmd_cursor,
									int b_flag, int pipetmp[2]);
void							handle_parent_process_logic(t_minishell *shell,
									t_command_list *cmd_cursor, int pipetmp[2]);
void							execute_child_process(t_minishell *shell,
									t_command_list *cmd_cursor,
									int b_flag, int pipetmp[2]);
void							setup_pipe_and_execute(t_minishell *shell,
									t_command_list *cmd_cursor,
									int b_flag);
t_redir_list					*setup_outfile_redirection(t_minishell *shell,
									t_redir_list *redir_list,
									int pipe_fd[2]);
t_redir_list					*setup_redirections(t_minishell *shell,
									t_redir_list *redir_list,
									int pipe_fd[2]);
int								ft_validate_syntax(t_minishell *shell);
void							ft_cmd_redir(t_minishell *shell, t_redir_list 
									*head, int r_flag);
int								ft_init_redirs(t_minishell *shell,
									t_command_list *cmd_cursor);
t_redir_list					*setup_heredoc_redirection(t_minishell *shell,
									t_redir_list *redir_list,
									int pipe_fd[2]);
t_redir_list					*setup_append_redirection(t_minishell *shell,
									t_redir_list *redir_list,
									int pipe_fd[2]);
t_redir_list					*setup_infile_redirection(t_minishell *shell,
									t_redir_list *redir_list,
									int pipe_fd[2]);
//HEREDOC
char							*ft_expand_err_hd(t_minishell *shell, 
									int i, char *hd);
void							exit_hd(t_minishell *shell);
void							ft_close(int fd);
#endif

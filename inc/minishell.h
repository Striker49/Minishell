/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   minishell.h                                        ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/09/20 16:44:14 by nomu                    ██║███████╗      */
/*   Updated: 2023/12/05 12:45:57 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

/*--- HEADER FILE NAME ---*/

#ifndef MINISHELL_H
# define MINISHELL_H

/*--- LIBRARIES ---*/

# define READLINE_LIBRARY
# define READLINE_HISTORY

# include "../inc/colors.h"
# include "../inc/env.h"
# include "../inc/error.h"
# include "../inc/exec.h"
# include "../inc/parsing.h"
# include "../inc/print.h"
# include "../inc/syntax.h"
# include "../inc/token.h"
# include "../libs/libft/inc/libft.h"
# include "../libs/readline/inc/history.h"
# include "../libs/readline/inc/readline.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdint.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <termios.h>

/*--- MAIN DATA STRUCTURES ---*/

typedef struct s_global
{
	int						fd;
	char					*delimiter;
	char					*line;
	volatile int			child;
	volatile int			stop;
	t_minishell				*shell;
}							t_global;

typedef struct s_token_list	t_token_list;
typedef struct s_executor	t_executor;

typedef struct s_minishell
{
	int						state;
	int						keep_ex;
	char					**envp;
	char					*prompt;
	unsigned int			exit_code;
	siginfo_t				*s_info;
	struct sigaction		action;
	struct termios			term;
	t_env_list				*env_lst;
	t_token_list			*tokens;
	t_errno					*error;
	t_executor				*exec;
	t_garbage_collector		*gc;
	t_garbage_collector		*gcn;
	t_tokenizer				*tokenizer;

}							t_minishell;

void						ft_boot_shell(t_minishell *shell, char **envp,
								int argc, char **argv);
void						ft_destroy_shell(t_minishell *shell);
void						ft_init_loop(t_minishell *shell, char **envp);
void						init_tokenizer(t_minishell *shell);
void						init_executor(t_minishell *shell);
void						init_error_handling(t_minishell *shell);
void						prompt_user(t_minishell *shell);
void						init_environment(t_minishell *shell, char **envp);
void						garbage_collector(t_minishell *shell);
int							ft_exit(t_minishell *shell,
								t_command_list *command_list);
void						reactivate_ctrl(void);
void						deactivate_ctrl(struct termios original_term);

#endif

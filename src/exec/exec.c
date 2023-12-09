/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:00:47 by seroy             #+#    #+#             */
/*   Updated: 2023/12/09 16:51:02 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	ft_check_directory(const char *input)
{
	struct stat	file_stat;

	if (!ft_strchr(input, '/'))
		return (0);
	if (stat(input, &file_stat) == -1)
		return (-1);
	if (S_ISDIR(file_stat.st_mode))
	{
		return (1);
	}
	else
		return (2);
	return (0);
}

int	check_file(t_minishell *shell, char **cmd)
{
	if (!access(cmd[0], X_OK))
		return (1);
	else if (ft_check_directory(cmd[0]) == 1)
	{
		print_err_msg("minishell: ", cmd[0], ": is a directory\n");
		shell->error->exit_code = 126;
		return (0);
	}
	print_err_msg("minishell: ", cmd[0], ": No such file or directory\n");
	shell->error->exit_code = 127;
	return (0);
}

int	try_cmd(t_minishell *shell, char **cmd, char *path, int i)
{
	char	*command;
	char	*path_cpy;
	char	**path_lst;

	command = ft_gc_strjoin(shell->gc, "/", cmd[0]);
	path_lst = ft_gc_split(shell->gc, &path[i], ':');
	i = 0;
	while (path_lst[i])
	{
		path_cpy = ft_gc_strdup(shell->gc, path_lst[i]);
		if (!access(ft_gc_strjoin(shell->gc, path_lst[i], command), F_OK)
			&& ft_strcmp(path_cpy, cmd[0]) != 0)
		{
			cmd[0] = ft_gc_strjoin(shell->gc, path_cpy, command);
			return (1);
		}
		i++;
	}
	if (path_lst[i] == 0)
	{
		print_err_msg("minishell: ", cmd[0], ": command not found\n");
		shell->error->exit_code = 127;
		return (0);
	}
	return (0);
}

int	verify_access(t_minishell *shell, char **cmd)
{
	struct stat	file_stat;

	if (stat(cmd[0], &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			print_err_msg("minishell: ", cmd[0], ": is a directory\n");
			shell->error->exit_code = 126;
		}
		else if (file_stat.st_mode & S_IXUSR)
			return (1);
		else
		{
			print_err_msg("minishell: ", cmd[0],
				": Permission denied\n");
			shell->error->exit_code = 126;
		}
	}
	else
	{
		print_err_msg("minishell: ", cmd[0],
			": No such file or directory\n");
		shell->error->exit_code = 127;
	}
	return (0);
}

int	validate_path(t_minishell *shell, char **cmd)
{
	int			i;
	char		*path;

	if (!cmd[0])
		return (1);
	if (ft_is_builtin(cmd[0]))
		return (1);
	if (ft_strncmp(cmd[0], "./", 2) == 0)
		return (verify_access(shell, cmd));
	if (cmd[0][0] == '/' || cmd[0][strlen(cmd[0]) - 1] == '/')
		return (check_file(shell, cmd));
	i = 0;
	path = find_path(shell->envp);
	if (!path)
	{
		print_err_msg("minishell: ", cmd[0],
			": No such file or directory\n");
		shell->error->exit_code = 127;
		return (0);
	}
	while (path[i] != '=')
		i++;
	i++;
	return (try_cmd(shell, cmd, path, i));
}

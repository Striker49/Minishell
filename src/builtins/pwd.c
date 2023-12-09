/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:37:40 by seroy             #+#    #+#             */
/*   Updated: 2023/12/01 14:39:53 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <limits.h>

void	ft_pwd(t_minishell *shell)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) != NULL)
		printf("%s\n", pwd);
	else
		printf("NO PWD VARIABLE\n");
	shell->error->exit_code = 0;
}

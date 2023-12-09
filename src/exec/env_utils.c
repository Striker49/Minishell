/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:45:39 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/01 13:53:03 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

int	count_key_len(char *env_elem)
{
	int	i;

	i = 0;
	while (env_elem[i] && env_elem[i] != '=')
		i++;
	return (i);
}

int	count_value_len(char *env_elem)
{
	int	i;

	i = 0;
	while (env_elem[i] && env_elem[i] != '=')
		i++;
	if (env_elem[i] == '=')
	{
		i++;
		return (ft_strlen(env_elem + i));
	}
	return (0);
}

char	*ft_get_env_key(t_garbage_collector *gc, char *env_elem)
{
	int		i;
	int		j;
	char	*key;
	int		key_len;

	i = 0;
	j = 0;
	key_len = count_key_len(env_elem);
	key = gc_malloc(gc, sizeof(char) * key_len + 1);
	if (!key)
		return (NULL);
	while (env_elem[i] && env_elem[i] != '=')
	{
		key[j] = env_elem[i];
		i++;
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*ft_get_env_value(t_garbage_collector *gc, char *env_elem)
{
	int		i;
	int		j;
	int		value_len;
	char	*value;

	i = 0;
	j = 0;
	value_len = count_value_len(env_elem);
	value = gc_malloc(gc, sizeof(char) * value_len + 1);
	if (!value)
		return (NULL);
	while (env_elem[i] && env_elem[i] != '=')
		i++;
	if (env_elem[i] == '=')
	{
		i++;
		while (env_elem[i])
			value[j++] = env_elem[i++];
		value[j] = '\0';
		return (value);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_atof_utils.c                                    ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/11/18 15:35:02 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:39:07 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_vars(t_atof *vars)
{
	vars->i = 0;
	vars->n = 1;
	vars->r = 0;
	vars->has_decimal = 0;
	vars->decimal_digits = 0;
}

void	ft_limits(t_atof *vars)
{
	if (vars->r > __LONG_MAX__ && vars->n == 1)
		exit(-1);
	if (vars->r < -__LONG_MAX__ && vars->n == -1)
		exit(-1);
}

void	ft_parse_integer(t_atof *vars, const char *str)
{
	if (!ft_isdigit(str[vars->i]))
		exit(-1);
	vars->r = vars->r * 10 + (str[vars->i] - '0');
	vars->i++;
}

void	ft_sign_handler(t_atof *vars, const char *str)
{
	if (str[vars->i] == '-')
		vars->n = -1;
	vars->i++;
}

void	ft_is_decimal(t_atof *vars, const char *str)
{
	vars->has_decimal = 1;
	vars->i++;
	while (ft_isdigit(str[vars->i]))
	{
		vars->r = vars->r * 10 + (str[vars->i] - '0');
		vars->decimal_digits++;
		vars->i++;
	}
}

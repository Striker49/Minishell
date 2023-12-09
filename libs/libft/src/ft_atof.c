/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_atof.c                                          ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/03/26 14:48:38 by nomu                    ██║███████╗      */
/*   Updated: 2023/11/18 15:38:33 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	t_atof	vars;

	ft_init_vars(&vars);
	while (ft_isspace(str[vars.i]))
		vars.i++;
	if (ft_issign(str[vars.i]))
		ft_sign_handler(&vars, str);
	while (ft_isdigit(str[vars.i]))
		ft_parse_integer(&vars, str);
	if (str[vars.i] == '.')
		ft_is_decimal(&vars, str);
	ft_limits(&vars);
	if (vars.has_decimal)
		vars.r /= powl(10.0L, vars.decimal_digits);
	return ((double)(vars.r * vars.n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:04:21 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/06 14:07:01 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

void	printf_err(char *format, char *var)
{
	int	i;

	i = -1;
	if (!format || !var)
		return ;
	while (format[++i])
	{
		if (format[i] == '$')
			ft_putstr_fd(var, 2);
		else
			write(2, &format[i], 1);
	}
}

int	is_valididentifier(char *arg)
{
	int		is_valid_first;
	int		is_valid_string;
	int		i;

	if (!arg)
		return (0);
	is_valid_first = (arg[0] == '_' || ft_isalpha(arg[0]));
	if (!is_valid_first)
		return (0);
	is_valid_string = 1;
	i = 0;
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			is_valid_string = 0;
		i++;
	}
	return (is_valid_string && is_valid_first);
}

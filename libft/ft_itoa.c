/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:58:12 by macote            #+#    #+#             */
/*   Updated: 2023/02/20 11:39:35 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_strlen.c"
// #include "ft_memset.c"
// #include "ft_strlcpy.c"

int	check_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*mal_str(int n)
{
	char	*str_;
	int		i;

	i = 0;
	if (n == 0)
		i = 1;
	if (check_negative(n))
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	str_ = malloc((sizeof(char)) * (i + 1));
	if (!str_)
		return (NULL);
	ft_memset(str_, '0', i);
	str_[i] = '\0';
	return (str_);
}

char	*case_min(void)
{
	char	*min_int;

	min_int = malloc(sizeof(char) * 12);
	if (!min_int)
		return (NULL);
	ft_strlcpy(min_int, "-2147483648", 12);
	return (min_int);
}

char	*ft_itoa(int n)
{
	int		i;
	int		reste;
	char	*str;
	int		str_len;

	if (n == -2147483648)
		return (case_min());
	i = 0;
	str = mal_str(n);
	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (check_negative(n))
	{
		str[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		reste = (n % 10) + 48;
		n /= 10;
		str[--str_len] = reste;
	}
	return (str);
}

// int main(void)
// {
// 	printf("%s", ft_itoa(-2147483648));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:02:05 by marugula          #+#    #+#             */
/*   Updated: 2022/03/28 19:09:13 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	lendigit(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*fill_str(char *str, int n, size_t len)
{
	size_t		i;
	long long	nd;

	nd = (long long) n;
	i = 0;
	if (nd < 0)
	{
		str[0] = '-';
		nd *= -1;
		i = 1;
	}
	while (len != i)
	{
		len--;
		str[len] = nd % 10 + 48;
		nd /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*rez;
	size_t	len;

	len = lendigit(n);
	rez = malloc((len + 1)*sizeof(char));
	if (rez == 0)
		return (0);
	return (fill_str(rez, n, len));
}

/*int main()
{
	printf("%s", ft_itoa(-2423331));
}*/

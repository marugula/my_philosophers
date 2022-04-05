/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:24 by marugula          #+#    #+#             */
/*   Updated: 2022/03/28 13:54:05 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isspace(char ch)
{
	if (ch == '\t' || ch == '\v' || ch == '\f'
		|| ch == '\r' || ch == '\n' || ch == ' ')
		return (1);
	return (0);
}

static int	math(char *str, int minus)
{
	long long	out;
	int			n;

	n = 0;
	out = 0;
	while ((*str >= 48 && *str < 58))
	{
		n++;
		out = out * 10 + (*str - 48);
		if (n >= 10)
		{
			if (out * minus > 2147483647)
				return (-1);
			else if (out * minus < -2147483648)
				return (0);
		}
		str++;
	}
	return ((int)out * minus);
}

int	check_symb(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') || str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}



int	ft_atoi(const char *nptr)
{
	char		*s;
	int			n;
	long long	out;
	int			minus;

	s = (char *)nptr;
	n = 0;
	out = 0;
	minus = 1;
	if (check_symb(s) == 0)
		return (-1);
	while (ft_isspace(*s))
		s++;
	if (*s == '+')
		s++;
	return (math(s, minus));
}

/*int main(int argv, char **argc)
{
	printf("%d\n", atoi(argc[1]));
	printf("%d\n", ft_atoi(argc[1]));   
}*/

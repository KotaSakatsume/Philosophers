/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/11 18:43:44 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_and_exit(t_data *data)
{
	free(data);
	exit(1);
}

static const char	*skip_whitespace_and_check_sign(const char *str,
		t_data *data)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			free_and_exit(data);
		str++;
	}
	return (str);
}

static long	parse_digits(const char *str, t_data *data, int *digit_seen)
{
	long	result;
	int		digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		*digit_seen = 1;
		if (result > (INT_MAX - digit) / 10)
			free_and_exit(data);
		result = result * 10 + digit;
		str++;
	}
	return (result);
}

int	safe_atoi(const char *str, t_data *data)
{
	int		digit_seen;
	long	result;

	digit_seen = 0;
	str = skip_whitespace_and_check_sign(str, data);
	result = parse_digits(str, data, &digit_seen);
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (!digit_seen || result == 0 || *str != '\0')
		free_and_exit(data);
	return ((int)result);
}

// int	main(int ac, char **av)
// {
// 	int	err;
// 	int	val;

// 	if (ac != 2)
// 		return (1);
// 	val = safe_atoi(av[1], &err);
// 	if (err)
// 		printf("変換エラーです\n");
// 	else
// 		printf("変換成功: %d\n", val);
// }

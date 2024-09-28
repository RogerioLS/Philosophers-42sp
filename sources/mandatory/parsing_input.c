/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:15:08 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/27 23:19:38 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

static inline bool	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*ft_valid_input(const char *string)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_is_space(*string))
		++string;
	if (*string == '+')
		++string;
	else if (*string == '-')
		ft_error_exit("Feed me only positive values!!!");
	if (!ft_is_digit(*string))
		ft_error_exit("The input is not a correct digit");
	number = string;
	while (ft_is_digit(*string++))
		++len;
	if (len > 10)
		ft_error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

static long	ft_atol(const char *string)
{
	long	num;

	num = 0;
	string = ft_valid_input(string);
	while (ft_is_digit(*string))
		num = (num * 10) + (*string++ - 48);
	if (num > INT_MAX)
		ft_error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}

void	ft_parse_input(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->philo_nbr > MAX_PHILOS)
		ft_error_exit(RED "\t\tError: Chill out, you're going to freeze the system.\n \
		If you're sure of what you're doing, change the max philos \n \
		macro in the philosophers.h file. Current max: 200"RESET);
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		ft_error_exit("User timestamps major than 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}

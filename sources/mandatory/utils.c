/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:50:09 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/27 20:19:53 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

long	ft_gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		ft_error_exit("Error: Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_error_exit("Wrong input to gettime!");
	return (1337);
}

void	ft_precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = ft_gettime(MICROSECOND);
	while (ft_gettime(MICROSECOND) - start < usec)
	{
		if (ft_simulation_finished(table))
			break ;
		elapsed = ft_gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (ft_gettime(MICROSECOND) - start < usec)
				;
	}
}

void	ft_clean(t_table *table)
{
	t_philosophers	*philo;
	int				i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		ft_safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	ft_safe_mutex_handle(&table->write_mutex, DESTROY);
	ft_safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->fork);
	free(table->philos);
}

void	ft_error_exit(const char *error_msg)
{
	printf(RED"%s\n"RESET, error_msg);
	exit(EXIT_FAILURE);
}

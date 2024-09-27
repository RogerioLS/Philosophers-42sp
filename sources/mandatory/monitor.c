/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:37:13 by codespace         #+#    #+#             */
/*   Updated: 2024/09/27 14:36:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

static bool	ft_philo_died(t_philosophers *philo)
{
	long	elapsed;
	long	t_to_die;

	if (ft_get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = ft_gettime(MILLISECOND) - ft_get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*ft_monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!ft_all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
		;
	while (!ft_simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !ft_simulation_finished(table))
		{
			if (ft_philo_died(table->philos + i))
			{
				ft_set_bool(&table->table_mutex, &table->end_simulation, true);
				ft_write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}

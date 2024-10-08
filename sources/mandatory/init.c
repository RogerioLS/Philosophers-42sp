/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:04:05 by codespace         #+#    #+#             */
/*   Updated: 2024/09/27 23:35:29 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

static void	ft_assign_fork(t_philosophers *philo, t_fork *fork, \
							int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &fork[(philo_position + 1) % philo_nbr];
	philo->second_fork = &fork[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[philo_position];
		philo->second_fork = &fork[(philo_position + 1) % philo_nbr];
	}
}

static void	ft_philo_init(t_table *table)
{
	int				i;
	t_philosophers	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		ft_safe_mutex_handle(&philo->philo_mutex, INIT);
		ft_assign_fork(philo, table->fork, i);
	}
}

void	ft_data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->all_threads_read = false;
	table->threads_running_nbr = 0;
	table->philos = ft_safe_malloc(sizeof(t_philosophers) * table->philo_nbr);
	table->fork = ft_safe_malloc(sizeof(t_fork) * table->philo_nbr);
	ft_safe_mutex_handle(&table->table_mutex, INIT);
	ft_safe_mutex_handle(&table->write_mutex, INIT);
	while (i < table->philo_nbr)
	{
		ft_safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i;
		i++;
	}
	ft_philo_init(table);
}

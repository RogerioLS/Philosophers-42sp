/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:33:52 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/27 15:08:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	*ft_lone_philo(void *arg)
{
	t_philosophers *philo;
	
	philo = (t_philosophers *)arg;
	ft_wait_all_thread(philo->table);
	ft_set_long(&philo->philo_mutex, &philo->last_meal_time, ft_gettime(MILLISECOND));
	ft_increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	ft_write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!ft_simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void ft_eat(t_philosophers *philo)
{
    ft_safe_mutex_handle(&philo->first_fork->fork, LOCK);
    ft_write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    ft_safe_mutex_handle(&philo->second_fork->fork, LOCK);
    ft_write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    ft_set_long(&philo->philo_mutex, &philo->last_meal_time, ft_gettime(MILLISECOND));
    philo->meals_counter++;
    ft_write_status(EATING, philo, DEBUG_MODE);
    ft_precise_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nbr_limit_meals > 0
        && philo->meals_counter == philo->table->nbr_limit_meals)
        ft_set_bool(&philo->philo_mutex, &philo->full, true);
    ft_safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    ft_safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*ft_dinner_simulation(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	ft_wait_all_thread(philo->table);
	ft_set_long(&philo->philo_mutex, &philo->last_meal_time, ft_gettime(MILLISECOND));
	ft_increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);

	while (!ft_simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		ft_eat(philo);
		ft_write_status(SLEEPING, philo, DEBUG_MODE);
		ft_precise_usleep(philo->table->time_to_sleep, philo->table);
	}
	return (NULL);
}

void	ft_dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		ft_safe_thread_handle(&table->philos[0].thread_id, ft_lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
		{
			ft_safe_thread_handle(&table->philos[i].thread_id,
				ft_dinner_simulation, &table->philos[i], CREATE);
		}
	}
	ft_safe_thread_handle(&table->monitor, ft_monitor_dinner, table, CREATE);
	table->start_simulation = ft_gettime(MILLISECOND);
	ft_set_bool(&table->table_mutex, &table->all_threads_read, true);

	i = -1;
	while (++i < table->philo_nbr)
		ft_safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	ft_set_bool(&table->table_mutex, &table->end_simulation, true);
	ft_safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}

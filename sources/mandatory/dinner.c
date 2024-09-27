/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:33:52 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/26 22:05:19 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	*ft_dinner_simulation(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	ft_wait_all_thread(philo->table);

	

	return (NULL);
}

void	ft_dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		ft_safe_handle_thread(&table->philos[i].thread_id,
			ft_dinner_simulation, &table->philos[i], CREATE);
	else
	{
		while (++i < table->philo_nbr)
		{
			ft_safe_handle_thread(&table->philos[i].thread_id,
				ft_dinner_simulation, &table->philos[i], CREATE);
			i++;
		}
	}
	table->start_simulation = ft_gettime(MILLISECOND);
	ft_set_bool(&table->table_mutex, &table->all_threads_read, true);

	i = -1;
	while (++i < table->philo_nbr)
		ft_safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:11:29 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/27 16:04:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	ft_wait_all_thread(t_table *table)
{
	while (!ft_get_bool(&table->table_mutex, &table->all_threads_read))
		;
}

bool	ft_all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool	ret;

    ret = false;
    ft_safe_mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = true;
    ft_safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

void	ft_increase_long(t_mtx *mutex, long *value)
{
	ft_safe_mutex_handle(mutex, LOCK);
	(*value)++;
	ft_safe_mutex_handle(mutex, UNLOCK);
}

void    ft_de_synchronize_philos(t_philosophers *philo)
{
    if (philo->table->philo_nbr % 2 == 0)
    {
        if (philo->id % 2 == 0)
            ft_precise_usleep(3e4, philo->table);
    }
    else
    {
        if (philo->id % 2)
            ft_thinking(philo, true);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirte.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:44:26 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/26 22:30:08 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	ft_write_status(t_philo_status status, t_philosophers *philo,
		bool debug)
{
	long	elapsed;

	elapsed = ft_gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	ft_safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d has taken a fork\n", \
			elapsed, philo->id);
		else if (EATING == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d is eating\n", \
			elapsed, philo->id);
		else if (SLEEPING == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d is sleeping\n", \
			elapsed, philo->id);
		else if (THINKING == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d is thinking\n", \
			elapsed, philo->id);
		else if (DIED == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d died\n", \
			elapsed, philo->id);
	}
	ft_safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

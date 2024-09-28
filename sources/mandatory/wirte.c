/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirte.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:44:26 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/27 23:34:57 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

static void	ft_write_status_debug(t_philo_status status, t_philosophers \
								*philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !ft_simulation_finished(philo->table))
		printf(WHITE"%6ld"RESET" %d has taken the 1° fork 🍴""\t\t\tn°"YELLOW \
		"[🍴 %d 🍴]\n"RESET, elapsed, philo->id, philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && \
			!ft_simulation_finished(philo->table))
		printf(WHITE"%6ld"RESET" %d has taken the 2° fork 🍴""\t\t\tn°"YELLOW \
		"[🍴 %d 🍴]\n"RESET, elapsed, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !ft_simulation_finished(philo->table))
		printf(WHITE"%6ld"CYAN" %d is eating 🍖""\t\t\t"YELLOW"[🍖 %ld 🍖]\n" \
		RESET, elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !ft_simulation_finished(philo->table))
		printf(WHITE"%6ld"RESET" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !ft_simulation_finished(philo->table))
		printf(WHITE"%6ld"RESET" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t😵😵😵 %6ld %d died 😵😵😵\n"RESET, elapsed, philo->id);
}

void	ft_write_status(t_philo_status status, t_philosophers *philo, \
						bool debug)
{
	long	elapsed;

	elapsed = ft_gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	ft_safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		ft_write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d has taken a fork\n", \
			elapsed, philo->id);
		else if (EATING == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !ft_simulation_finished(philo->table))
			printf(WHITE "%-6ld"RESET" %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(WHITE "%-6ld"RESET" %d died\n", elapsed, philo->id);
	}
	ft_safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

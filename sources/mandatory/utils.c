/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:50:09 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/26 21:43:38 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

long	ft_gettime(t_time_code time_code)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		error_exit("Error: Gettimeofday failed");
	if (time_code == SECOND)
		return (current_time.tv_sec + (current_time.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return (current_time.tv_sec * 1e3 + (current_time.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return (current_time.tv_sec * 1e6 + current_time.tv_usec);
	else
		error_exit("Wrong input to gettime!");
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

void	ft_error_exit(const char *error_msg)
{
	printf(RED"%s\n"RESET, error_msg);
	exit(EXIT_FAILURE);
}

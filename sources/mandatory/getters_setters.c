/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:56:44 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/26 21:04:25 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	ft_set_bool(t_mtx	*mutex, bool *dst, bool value)
{
	ft_safe_mutex_handle(mutex, LOCK);
	*dst = value;
	ft_safe_mutex_handle(mutex, UNLOCK);
}

bool	ft_get_bool(t_mtx *mutex, bool *value)
{
	bool	retrieved;

	ft_safe_mutex_handle(mutex, LOCK);
	retrieved = *value;
	ft_safe_mutex_handle(mutex, UNLOCK);
	return (retrieved);
}

long	ft_get_long(t_mtx *mutex, long *value)
{
	long	retrieve;

	ft_safe_mutex_handle(mutex, LOCK);
	retrieve = *value;
	ft_safe_mutex_handle(mutex, UNLOCK);
	return (retrieve);
}

void	ft_set_long(t_mtx *mutex, long *dst, long value)
{
	ft_safe_mutex_handle(mutex, LOCK);
	*dst = value;
	ft_safe_mutex_handle(mutex, UNLOCK);
}

bool	ft_simulation_finished(t_table *table)
{
	return (ft_get_bool(&table->table_mutex, &table->end_simulation));
}

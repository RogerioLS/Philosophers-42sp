/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:11:29 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/26 21:15:02 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	ft_wait_all_thread(t_table *table)
{
	while (!ft_get_bool(&table->table_mutex, &table->all_threads_read))
		;
}

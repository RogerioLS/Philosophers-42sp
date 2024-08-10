/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:32:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/08/10 18:11:41 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Input Error\n"
			YELLOW "Please enter: ./philo <no. of philos> <time_to_die>"
			" <time_to_eat> <time_to_sleep> <max_meals> (optional)\n"
			"For example: ./philo 5 800 200 200 7" RESET);
	}
}

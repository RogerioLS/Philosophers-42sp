/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:50:09 by roglopes          #+#    #+#             */
/*   Updated: 2024/08/10 19:03:08 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	ft_error_exit(const char *error_msg)
{
	printf(RED"%s\n"RESET, error_msg);
	exit(EXIT_FAILURE);
}

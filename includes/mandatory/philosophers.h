/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:57:22 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/25 00:43:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
// https://github.com/Thuggonaut/42IC_Ring03_Philosophers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

//ANSI Escape Sequences for text formatting*****
# define RESET		"\033[0m" //Reset to default color 
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

/*
 * OpCode form mutex | thread functions
 */
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}			t_opcode;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

/**
 * PHILO
 * 
 *  ./philo 5 800 200 200 [5]
 * 
 */
typedef struct s_philosophers
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philosophers;

/**
 * TABLE
 * 
 * ./philo 5 800 200 200 [5]
 */
typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	t_fork			*fork;
	t_philosophers	*philos;
}				t_table;

//SIMULATION*****
void		ft_parse_input(t_table *table, char *argv[]);

//UTILS*****
void		ft_error_exit(const char *error_msg);

//SAFE FUNCTIONS****
void    	*ft_safe_malloc(size_t bytes);
void    	ft_safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void   		ft_safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
        	void *data, t_opcode opcode);
#endif
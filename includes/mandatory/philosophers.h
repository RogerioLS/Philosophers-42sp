/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:57:22 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/27 16:06:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
// https://github.com/Thuggonaut/42IC_Ring03_Philosophers
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// ANSI Escape Sequences for text formatting*****
# define RESET "\033[0m" // Reset to default color
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

# define DEBUG_MODE 1

/*
 * PHILO STATES
*/
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;


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

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/**
 * PHILO
 *
 *  ./philo 5 800 200 200 [5]
 *
 */
typedef struct s_philosophers
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philosophers;

/**
 * TABLE
 *
 * ./philo 5 800 200 200 [5]
 */
typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_read;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*fork;
	t_philosophers		*philos;
}						t_table;

// SIMULATION*****
void					ft_parse_input(t_table *table, char *argv[]);

// UTILS*****
void					ft_error_exit(const char *error_msg);
long					ft_gettime(t_time_code time_code);
void					ft_precise_usleep(long usec, t_table *table);

// INIT*****
void					ft_data_init(t_table *table);

	// SAFE FUNCTIONS****
void					*ft_safe_malloc(size_t bytes);
void					ft_safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					ft_safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);

void					ft_wait_all_thread(t_table *table);

void					ft_set_bool(t_mtx *mutex, bool *dst, bool value);
bool					ft_get_bool(t_mtx *mutex, bool *value);
long					ft_get_long(t_mtx *mutex, long *value);
void					ft_set_long(t_mtx *mutex, long *dst, long value);
bool					ft_simulation_finished(t_table *table);

void					ft_write_status(t_philo_status status, t_philosophers *philo,
						bool debug);
void					ft_dinner_start(t_table *table);
void					*ft_monitor_dinner(void *data);
void					ft_increase_long(t_mtx *mutex, long *value);
bool					ft_all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void					ft_clean(t_table *table);
void					ft_thinking(t_philosophers *philo, bool pre_simulation);
void    				ft_de_synchronize_philos(t_philosophers *philo);

#endif
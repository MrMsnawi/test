/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmardi <rmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:58:27 by rmardi            #+#    #+#             */
/*   Updated: 2025/08/03 23:28:22 by rmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define MAX_FORKS 200
# define MAX_PHILOS 200

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	struct s_data	*data;
	pthread_t		thread_id;
	int				left_fork;
	int				right_fork;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long			start_time;
	pthread_mutex_t	forks[MAX_FORKS];
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	int				someone_died;
}	t_data;

int		ft_atoi(const char *str);
void	ft_usleep(long microseconds, t_philo *philo);
int		meals_eaten(t_data *data);
int		check_death(t_data *data);
int		initialize_data(int ac, char **av, t_data *data);
time_t	get_time(void);
int		initialize_philos(t_data *data);
void	*philo_routine(void *ph);
int		eating(t_philo *philo);
int		sleeping_thinking(t_philo *philo);
int		validate_args(int ac, char **av);
void	cleanup(t_data *data);

#endif
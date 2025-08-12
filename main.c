/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmardi <rmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:19:56 by rmardi            #+#    #+#             */
/*   Updated: 2025/08/03 23:29:04 by rmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meals_eaten(t_data *data)
{
	int	i;
	int	count;

	if (data->meals_required == -1)
		return (0);
	count = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten >= data->meals_required)
			count++;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	if (count == data->philo_count)
		return (1);
	return (0);
}

int	check_death(t_data *data)
{
	int		i;
	long	current_time;
	long	time_since_meal;

	i = 0;
	current_time = get_time();
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		time_since_meal = current_time - data->philos[i].last_meal_time;
		if (time_since_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_lock(&data->death_lock);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n", get_time() - data->start_time,
				data->philos[i].id);
			return (pthread_mutex_unlock(&data->print_lock), 1);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (0);
}

int	start_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&data->philos[i].thread_id,
			NULL, philo_routine, &data->philos[i]);
		i++;
	}
	while (1)
	{
		if (check_death(data))
			break ;
		if (meals_eaten(data) == 1)
			break ;
		usleep(100);
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (1);
}

int	initialize_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!validate_args(ac, av))
		return (1);
	if (!initialize_data(ac, av, &data))
		return (1);
	if (!initialize_philos(&data))
		return (1);
	if (!start_process(&data))
	{
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}

#include "philo.h"

static int	validate_philo_count(t_data *data, char *arg)
{
	data->philo_count = ft_atoi(arg);
	if (data->philo_count <= 0 || data->philo_count > MAX_PHILOS)
	{
		printf("invalid arguments.");
		return (0);
	}
	return (1);
}

static int	validate_timings(t_data *data, char **av)
{
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
	{
		printf("invalid arguments.");
		return (0);
	}
	return (1);
}

static int	validate_meals(int ac, char **av, t_data *data)
{
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required <= 0)
		{
			printf("invalid arguments.");
			return (0);
		}
	}
	else
		data->meals_required = -1;
	return (1);
}

static void	init_mutexes(t_data *data)
{
	data->start_time = get_time();
	data->someone_died = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
}

int	initialize_data(int ac, char **av, t_data *data)
{
	if (!validate_philo_count(data, av[1]))
		return (0);
	if (!validate_timings(data, av))
		return (0);
	if (!validate_meals(ac, av, data))
		return (0);
	init_mutexes(data);
	return (1);
}

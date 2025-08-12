#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->death_lock);
}

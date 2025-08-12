#include "philo.h"

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (!philo)
		return (NULL);
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d has taken a fork\n",
			get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		ft_usleep(philo->data->time_to_die, philo);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		if (!eating(philo))
			return (NULL);
		if (!sleeping_thinking(philo))
			return (NULL);
	}
	return (NULL);
}

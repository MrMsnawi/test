#include "philo.h"

int	assign_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died
		|| philo->meals_eaten == philo->data->meals_required)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	*first_fork = philo->left_fork;
	*second_fork = philo->right_fork;
	return (1);
}

int	lock_right_fork(t_philo *philo, int first_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died
		|| philo->meals_eaten == philo->data->meals_required)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died)
		printf("%ld %d has taken a fork\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (1);
}

int	lock_left_fork(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died
		|| philo->meals_eaten == philo->data->meals_required)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died)
		printf("%ld %d has taken a fork\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (1);
}

int	eating(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (!assign_forks(philo, &first_fork, &second_fork))
		return (0);
	if (!lock_right_fork(philo, first_fork))
		return (0);
	if (!lock_left_fork(philo, first_fork, second_fork))
		return (0);
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died)
		printf("%ld %d is eating\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	return (1);
}

int	sleeping_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died
		|| philo->meals_eaten == philo->data->meals_required)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died)
		printf("%ld %d is sleeping\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
	ft_usleep(philo->data->time_to_sleep, philo);
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->someone_died
		|| philo->meals_eaten == philo->data->meals_required)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died)
		printf("%ld %d is thinking\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (1);
}

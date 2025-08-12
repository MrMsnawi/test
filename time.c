#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int is_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	int died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_lock);
	if (died)
	{
		return 1;
	}	
	return 0;
}

void	ft_usleep(long n, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < n && !is_died(philo))
	{
		usleep(500);
	}
}

#include "philo.h"

int	validate_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 6 && ac != 5)
	{
		printf("invalid arguments.");
		return (0);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("invalid arguments.");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

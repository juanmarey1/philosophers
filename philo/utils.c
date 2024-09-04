#include "inc/philo.h"

void	ft_destroy_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eat);
	if (data->philo_threads)
		free(data->philo_threads);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

int	ft_error(char *str, t_data	*data)
{
	printf("%s\n", str);
	if (data)
		ft_destroy_data(data);
	return (1);
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000
		+ (time.tv_usec / 1000));
}

void	ft_usleep(int	time)
{
	int	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(500);
}
#include "inc/philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].eat = &(data->eat_mutex[i]);
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->init, NULL);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->eat_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->eat_mutex)
	{
		free(data->philos);
		free(data->forks);
		free(data->philo_threads);
		return (ft_error(MALLOC_ERR, NULL));
	}
	while(++i < data->philo_num)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		pthread_mutex_init(&(data->eat_mutex[i]), NULL);
	}
	data->philos[0].l_fork = &(data->forks[0]);
	data->philos[0].r_fork = &(data->forks[data->philo_num - 1]);
	i = 0;
	while (++i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
	return (0);
}

int	init_alloc(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (ft_error(MALLOC_ERR, NULL));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		free(data->philos);
		return (ft_error(MALLOC_ERR, NULL));
	}
	data->philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->philo_threads)
	{
		free(data->forks);
		free(data->philos);
		return (ft_error(MALLOC_ERR, NULL));
	}
	return (0);
}

int	init_all(char **argv, t_data *data)
{
	data->philo_num = ft_atoi(argv[1]);
	data->death_t = (size_t)ft_atoi(argv[2]);
	data->eat_t = (size_t)ft_atoi(argv[3]);
	data->sleep_t = (size_t)ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = (size_t)ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
	data->finished = 0;
	data->dead = 0;
	data->start_t = 0;
	data->init_mutex = 1;
	if (init_alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philo(data);
	return (0);
}
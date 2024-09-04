#include "inc/philo.h"

void	*monitor(void	*philo)
{
	t_philo	*supervisor;
	int		i;

	supervisor = (t_philo *)philo;
	supervisor->data->start_t = get_current_time();
	while (supervisor->data->dead == 0 && supervisor->data->finished < supervisor->data->philo_num)
	{
		pthread_mutex_lock(&supervisor->data->eat);
		i = -1;
		while (++i < supervisor->data->philo_num && supervisor->data->dead == 0)
		{
			if (supervisor->data->finished == supervisor->data->philo_num)
				break ;
			if (((get_current_time() - supervisor->data->philos[i].last_ate) > supervisor->data->death_t) && supervisor->data->philos[i].eating != 1)
			{
				supervisor->data->dead = 1;
				ft_messages(DEAD, &supervisor->data->philos[i]);
			}
		}
		pthread_mutex_unlock(&supervisor->data->eat);
	}
	return ((void *)0);
}

void	*routine(void	*argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	while (philo->data->dead == 0 && philo->data->finished < philo->data->philo_num)
	{
		ft_eat(philo);
		ft_messages(THINK, philo);
	}
	return ((void *)0);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_create(data->monitor_thread, NULL, &monitor, &data->monitor))
		ft_error(ERR_MONITOR, data);
	while (++i < data->philo_num)
	{
		data->philos[i].last_ate = get_current_time();
		if (pthread_create(data->philo_threads[i], NULL, &routine, &data->philos[i]))
			ft_error(ERR_PHILO, data);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philo_threads[i], NULL))
			ft_error(ERR_JOIN, data);
	}
	return (0);
}